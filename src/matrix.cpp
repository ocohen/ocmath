#include <matrix.hpp>

using namespace oc;

//Assuming row major
#define DataFrom(array, col, row) array[col * 4 + row]
#define Data(col,row) DataFrom(mData, row, col)

#ifdef SIMDV
#undef SIMDV
#endif

#ifdef OC_SIMD
#define SIMDV(name, vector) __m128 * name = (__m128*) vector 
#endif

std::ostream & operator<<(std::ostream & o, const oc::Matrix & rhs)
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
    return vector4( Data(0, index), Data(1, index), Data(2, index), Data(3, index) );
}

vector4 Matrix::GetRow(int index)
{
    return vector4(Data(index,0), Data(index,1), Data(index,2), Data(index,3) );
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
    out[0] = v[0] * Data(0,0) + v[1] * Data(0, 1) + v[2] * Data(0, 2) + v[3] * Data(0, 3);
    out[1] = v[0] * Data(1,0) + v[1] * Data(1, 1) + v[2] * Data(1, 2) + v[3] * Data(1, 3);
    out[2] = v[0] * Data(2,0) + v[1] * Data(2, 1) + v[2] * Data(2, 2) + v[3] * Data(2, 3);
    out[3] = v[0] * Data(3,0) + v[1] * Data(3, 1) + v[2] * Data(3, 2) + v[3] * Data(3, 3);
#endif

    return vector4(out[0], out[1], out[2], out[3]);
}

Matrix Matrix::operator*(const Matrix & rhs) const
{
    scalar output[16];
    const scalar * data = rhs.GetData();

#ifdef OC_SIMD
    scalar * out = output;

    //we need to multiply rhs by each row in *this, and save it as each column

        SIMDV(c1, out);
        SIMDV(col, data);
        *c1 = _mm_load1_ps(mData);
        __m128 c2 = _mm_load1_ps(mData + 4);
        __m128 c3 = _mm_load1_ps(mData + 8);
        __m128 c4 = _mm_load1_ps(mData + 12);
        __m128 c5 = _mm_load1_ps(mData + 1);
        __m128 c6 = _mm_load1_ps(mData + 5);
        __m128 c7 = _mm_load1_ps(mData + 9);
        __m128 c8 = _mm_load1_ps(mData + 13);
        __m128 c9 = _mm_load1_ps(mData + 2);
        __m128 c10 = _mm_load1_ps(mData + 6);
        __m128 c11 = _mm_load1_ps(mData + 10);
        __m128 c12 = _mm_load1_ps(mData + 14);
        __m128 c13 = _mm_load1_ps(mData + 3);
        __m128 c14 = _mm_load1_ps(mData + 7);
        __m128 c15 = _mm_load1_ps(mData + 11);
        __m128 c16 = _mm_load1_ps(mData + 15);

        //first column
        *c1 = _mm_mul_ps(*col++, *c1);
        c2 = _mm_mul_ps(*col++,  c2);
        c3 = _mm_mul_ps(*col++,  c3);
        c4 = _mm_mul_ps(*col++,  c4);

        *c1 = _mm_add_ps(*c1, c2);
        c3 = _mm_add_ps(c3, c4);
        *c1 = _mm_add_ps(*c1, c3);
        c1 ++;


        //second column

        col = (__m128 *) data;

        *c1 = _mm_mul_ps(*col++, c5);
        c6 = _mm_mul_ps(*col++,  c6);
        c7 = _mm_mul_ps(*col++,  c7);
        c8 = _mm_mul_ps(*col++,  c8);

        *c1 = _mm_add_ps(*c1, c6);
        c7 = _mm_add_ps(c7, c8);
        *c1 = _mm_add_ps(*c1, c7);
        c1 ++;

        //third column
        col = (__m128 *) data;
        *c1 = _mm_mul_ps(*col++, c9);
        c10 = _mm_mul_ps(*col++,  c10);
        c11 = _mm_mul_ps(*col++,  c11);
        c12 = _mm_mul_ps(*col++,  c12);

        *c1 = _mm_add_ps(*c1, c10);
        c11 = _mm_add_ps(c11, c12);
        *c1 = _mm_add_ps(*c1, c11);
        c1 ++;

        //fourth column
        col = (__m128 *) data;
        *c1 = _mm_mul_ps(*col++, c13);
        c14 = _mm_mul_ps(*col++,  c14);
        c15 = _mm_mul_ps(*col++,  c15);
        c16 = _mm_mul_ps(*col++,  c16);

        *c1 = _mm_add_ps(*c1, c14);
        c15 = _mm_add_ps(c15, c16);
        *c1 = _mm_add_ps(*c1, c15);
        c1 ++;
#else
        for(int c = 0; c<4; ++c)
        {
            for(int r = 0; r < 4; ++r)
            {
                DataFrom(output, r, c) = Data(r,0) * DataFrom(data, 0,c) + Data(r, 1) * DataFrom(data, 1,c) + Data(r,2) * DataFrom(data, 2, c) + Data(r,3) * DataFrom(data, 3, c);
            }
        }
#endif

        return Matrix(output);
}
#undef Data(row, col)
#undef DATA(array, row, col)
