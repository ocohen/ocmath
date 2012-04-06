#include <vector3.hpp>
#include <iostream>
#include <simd.hpp>

std::ostream & operator<<(std::ostream & o, const ocmath::vector3 & rhs)
{
    o << "(" << rhs.X() << "," << rhs.Y() << "," << rhs.Z() << ")";
    return o;
}

using namespace ocmath;

vector3::vector3(){}

vector3::vector3(scalar x, scalar y, scalar z) : vector4(x,y,z,0.0){}

vector3::vector3(const vector3 & rhs) : vector4( rhs.mX, rhs.mY, rhs.mZ, 0.0 ) {}

vector3 vector3::Cross(const vector3 & rhs ) const
{
#ifdef OC_SIMD
    SIMDV(left, *this);
    SIMDV(right, rhs);

    //need to swap middle elements (y and z)   (11 01 10 0)
    int firstSwap = _MM_SHUFFLE(3, 0, 2, 1);
    //need to swap first elements (x and y) (10 11 01 0)
    int secondSwap = _MM_SHUFFLE(3, 1, 0, 2);

    __m128 left1 = _mm_shuffle_ps(*left, *left, firstSwap);
    __m128 right1= _mm_shuffle_ps(*right, *right, secondSwap);
    __m128 mult1 = _mm_mul_ps(left1, right1);

    __m128 left2 = _mm_shuffle_ps(*left, *left, secondSwap);
    __m128 right2= _mm_shuffle_ps(*right, *right, firstSwap);
    __m128 mult2 = _mm_mul_ps(left2, right2);

    vector3 v;

    __m128 * result = (__m128 *) &v.mX; 

    *result = _mm_sub_ps(mult1, mult2);

    return v;

#else
    scalar i = mY * rhs.mZ - mZ * rhs.mY;
    scalar j = mX * rhs.mZ - mZ * rhs.mX;
    scalar k = mX * rhs.mY - mY * rhs.mX;

    return vector3(i, -j, k);
#endif
}
