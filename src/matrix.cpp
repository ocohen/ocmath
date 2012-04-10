#include <matrix.hpp>

using namespace ocmath;

//Assuming row major
#define DataFrom(array, col, row) array[col * 4 + row]
#define Data(col,row) DataFrom(mData, row, col)

#ifdef SIMDV
#undef SIMDV
#endif

#ifdef OC_SIMD
#define SIMDV(name, vector) __m128 * name = (__m128*) vector 
#endif

std::ostream & operator<<(std::ostream & o, const ocmath::Matrix & rhs)
{
    const scalar * mData = rhs.GetData();    //only calling it mData for the sake of the macro
    o << std::endl;
    o << "[ " << Data(0,0) << "," << Data(0,1) << "," << Data(0,2) << "," << Data(0,3) << std::endl;
    o << "  " << Data(1,0) << "," << Data(1,1) << "," << Data(1,2) << "," << Data(1,3) << std::endl;
    o << "  " << Data(2,0) << "," << Data(2,1) << "," << Data(2,2) << "," << Data(2,3) << std::endl;
    o << "  " << Data(3,0) << "," << Data(3,1) << "," << Data(3,2) << "," << Data(3,3) << " ]" << std::endl;
    return o;
}

Matrix::Matrix(scalar * data)
{
    for(int i=0; i<16; i++)
    {
        mData[i] = data[i];
    }
}

Matrix Matrix::Identity()
{
    scalar data[] = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f};
    return Matrix(data);
}

vector4 Matrix::GetColumn(int index)
{
    int c1 = Data(0, index);
    int c2 = Data(1, index);
    int c3 = Data(2, index);
    int c4 = Data(3, index);
    return vector4( mData[c1], mData[c2], mData[c3], mData[c4] ); 
}

vector4 Matrix::GetRow(int index)
{
    int c1 = Data(index, 0);
    int c2 = Data(index, 1);
    int c3 = Data(index, 2);
    int c4 = Data(index, 3);
    return vector4( mData[c1], mData[c2], mData[c3], mData[c4] ); 
}

vector4 Matrix::operator*(const vector4 & X)
{
#ifdef OC_SIMD
    const scalar * v = X.GetData();
    float out[4];
    SIMDV(c1, out);
    *c1 = _mm_load1_ps(v);
    __m128 c2 = _mm_load1_ps(v+1);
    __m128 c3 = _mm_load1_ps(v+2);
    __m128 c4 = _mm_load1_ps(v+3);

    SIMDV(col, mData);

    *c1 = _mm_mul_ps(*col++, *c1);
    c2 = _mm_mul_ps(*col++, c2);
    c3 = _mm_mul_ps(*col++, c3);
    c4 = _mm_mul_ps(*col++, c4);
    *c1 = _mm_add_ps(*c1, c2);
    c3 = _mm_add_ps(c3, c4);
    *c1 = _mm_add_ps(*c1, c3);

    return vector4(out[0], out[1], out[2], out[3]);
#else
    const scalar * v = X.GetData();
    scalar x = v[0] * Data(0,0) + v[1] * Data(0, 1) + v[2] * Data(0, 2) + v[3] * Data(0, 3);
    scalar y = v[0] * Data(1,0) + v[1] * Data(1, 1) + v[2] * Data(1, 2) + v[3] * Data(1, 3);
    scalar z = v[0] * Data(2,0) + v[1] * Data(2, 1) + v[2] * Data(2, 2) + v[3] * Data(2, 3);
    scalar w = v[0] * Data(3,0) + v[1] * Data(3, 1) + v[2] * Data(3, 2) + v[3] * Data(3, 3);
    return vector4(x,y,z,w);
#endif
}

Matrix Matrix::operator*(const Matrix & rhs)
{
    scalar output[16];
    const scalar * data = rhs.GetData();

    for(int c = 0; c<4; ++c)
    {
        for(int r = 0; r < 4; ++r)
        {
            DataFrom(output, r, c) = Data(r,0) * DataFrom(data, 0,c) + Data(r, 1) * DataFrom(data, 1,c) + Data(r,2) * DataFrom(data, 2, c) + Data(r,3) * DataFrom(data, 3, c);
        }
    }

    return Matrix(output);
}
#undef Data(row, col)
#undef DATA(array, row, col)
