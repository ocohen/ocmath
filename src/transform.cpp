#include <transform.hpp>
#include <vector.hpp>

#ifdef SIMDV
#undef SIMDV
#endif

#ifdef OC_SIMD
#define SIMDV(name, vector) __m128 * name = (__m128*) vector 
#endif
using namespace oc;

Transform::Transform(scalar * data)
{
    for(int i = 0; i < 16; i++)
    {
        mData[i] = data[i];
    }

    mData[3] = 0;
    mData[7] = 0;
    mData[11] = 0;
    mData[15] = 1;
}

Transform::Transform(const Matrix & rhs) : Matrix(rhs)
{
    mData[3] = 0;
    mData[7] = 0;
    mData[11] = 0;
    mData[15] = 1;
}

Transform::Transform(const Transform & rhs) : Matrix(rhs)
{
}

point3 Transform::GetOrigin() const
{
    return point3(mData[12], mData[13], mData[14]);
}

void Transform::SetOrigin(const point3 & origin)
{
    mData[12] = origin.X();
    mData[13] = origin.Y();
    mData[14] = origin.Z();
}

Transform Transform::operator*(const Transform & rhs) const
{
    scalar output[16];
    const scalar * data = rhs.GetData();

#ifdef OC_SIMD
    scalar * out = output;
    SIMDV(c1, out);

    for(int i=0; i< 12; i += 4)
    {
        *c1 = _mm_load1_ps(data + i);
        __m128 c2 = _mm_load1_ps(data + 1 + i);
        __m128 c3 = _mm_load1_ps(data + 2 + i);

        SIMDV(col, mData);

        //first row
        *c1 = _mm_mul_ps(*col++, *c1);
        c2 = _mm_mul_ps(*col++, c2);
        c3 = _mm_mul_ps(*col++, c3);
        *c1 = _mm_add_ps(*c1, c2);
        *c1 = _mm_add_ps(*c1, c3);

        ++c1;

    }
    *c1 = _mm_load1_ps(data + 12);
    __m128 c2 = _mm_load1_ps(data + 13);
    __m128 c3 = _mm_load1_ps(data + 14);

    SIMDV(col, mData);

    //first row
    *c1 = _mm_mul_ps(*col++, *c1);
    c2 = _mm_mul_ps(*col++, c2);
    c3 = _mm_mul_ps(*col++, c3);
    *c1 = _mm_add_ps(*c1, c2);
    c3 = _mm_add_ps(c3, *col++);
    *c1 = _mm_add_ps(*c1, c3);

#else
    for(int r = 0; r<3; ++r)
    {
        for(int c = 0; c<3; ++c)
        {
            DataFrom(output, r, c) = DataFrom(data,r,0) * Data(0,c) + DataFrom(data,r, 1) * Data( 1,c) + DataFrom(data, r,2) * Data( 2, c);
        }
    }

    for(int c=0; c<3; ++c)
    {
        DataFrom(output, 3, c) = DataFrom(data, 3, 0) * Data(0, c) + DataFrom(data,3, 1) * Data(1, c) + DataFrom(data,3,2) * Data(2, c) + Data(3, c);  
    }
    DataFrom(output, 3, 3) = 1.0f; 
#endif

    return Transform(output);
}
