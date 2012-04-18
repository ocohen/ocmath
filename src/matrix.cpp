#include <matrix.hpp>

using namespace oc;


#ifdef SIMDV
#undef SIMDV
#endif

#ifdef OC_SIMD
#define SIMDV(name, vector) __m128 * name = (__m128*) vector 
#endif

std::ostream & operator<<(std::ostream & o, const oc::Matrix & rhs)
{
    //Format output in regular matrix format
    const scalar * mData = rhs.GetData();
    o << std::endl;
    o << "[ " << mData[0] << "," << mData[4] << "," << mData[8] << "," << mData[12] << std::endl;
    o << "  " << mData[1] << "," << mData[5] << "," << mData[9] << "," << mData[13] << std::endl;
    o << "  " << mData[2] << "," << mData[6] << "," << mData[10] << "," << mData[14] << std::endl;
    o << "  " << mData[3] << "," << mData[7] << "," << mData[11] << "," << mData[15] << " ]";
    return o;
}

Matrix::Matrix(scalar * data)
{
    memcpy(mData, data, 16 * sizeof(scalar) );
}

Matrix::Matrix(const Matrix & rhs)
{
    memcpy(mData, rhs.mData, 16 * sizeof(scalar) );
}

Matrix Matrix::Identity()
{
    scalar data[] = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f};
    return Matrix(data);
}

vector4 Matrix::GetColumn(int index)    //matrix column (so for our representation it's actually a row)
{
    return vector4( Data(index, 0), Data(index, 1), Data(index, 2), Data(index, 3) );
}

void Matrix::SetColumn(int index, const vector4 & v) //matrix column (for us it's a row)
{
    memcpy(mData + index*4, v.GetData(), sizeof(vector4) );
}

vector4 Matrix::GetRow(int index)   //matrix row (so for us it's a column)
{
    return vector4(Data(0,index), Data(1,index), Data(2,index), Data(3,index) );
}

void Matrix::SetRow(int index, const vector4 & v)   //matrix row (so for us it's column)
{
    Data(0, index) = v.X();
    Data(1, index) = v.Y();
    Data(2, index) = v.Z();
    Data(3, index) = v.W();
}

vector4 Matrix::operator*(const vector4 & X) const
{
    const scalar * __restrict v = X.GetData();
    scalar out[4];
#ifdef OC_SIMD
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

#else
    out[0] = v[0] * Data(0,0) + v[1] * Data(1, 0) + v[2] * Data(2, 0) + v[3] * Data(3, 0);
    out[1] = v[0] * Data(0,1) + v[1] * Data(1, 1) + v[2] * Data(2, 1) + v[3] * Data(3, 1);
    out[2] = v[0] * Data(0,2) + v[1] * Data(1, 2) + v[2] * Data(2, 2) + v[3] * Data(3, 2);
    out[3] = v[0] * Data(0,3) + v[1] * Data(1, 3) + v[2] * Data(2, 3) + v[3] * Data(3, 3);
#endif

    return vector4(out[0], out[1], out[2], out[3]);
}

Matrix Matrix::operator*(const Matrix & rhs) const
{
    scalar output[16];
    const scalar * data = rhs.GetData();

#ifdef OC_SIMD
    scalar * out = output;
    SIMDV(c1, out);

    for(int i=0; i< 16; i += 4)
    {
        *c1 = _mm_load1_ps(data + i);
        __m128 c2 = _mm_load1_ps(data + 1 + i);
        __m128 c3 = _mm_load1_ps(data + 2 + i);
        __m128 c4 = _mm_load1_ps(data + 3 + i);

        SIMDV(col, mData);

        //first row
        *c1 = _mm_mul_ps(*col++, *c1);
        c2 = _mm_mul_ps(*col++, c2);
        c3 = _mm_mul_ps(*col++, c3);
        c4 = _mm_mul_ps(*col++, c4);
        *c1 = _mm_add_ps(*c1, c2);
        c3 = _mm_add_ps(c3, c4);
        *c1 = _mm_add_ps(*c1, c3);

        ++c1;

    }

#else
    for(int r = 0; r<4; ++r)
    {
        for(int c = 0; c<4; ++c)
        {
            DataFrom(output, r, c) = DataFrom(data, r,0) * Data(0,c) + DataFrom(data, r, 1) * Data(1,c) + DataFrom(data, r,2) * Data( 2, c) + DataFrom(data,r,3) * Data(3, c);
        }
    }
#endif

    return Matrix(output);
}
#undef Data(row, col)
#undef DATA(array, row, col)
