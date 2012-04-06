#include <vector4.hpp>
#include <iostream>
#include <cmath>

#ifdef OC_SIMD
#include <xmmintrin.h>
#include <pmmintrin.h>
#endif

using namespace ocmath;

//make it nice to print to screen
std::ostream & operator<<(std::ostream & o, const ocmath::vector4 & rhs)
{
    o << "(" << rhs.X() << "," << rhs.Y() << "," << rhs.Z() << "," << rhs.W() << ")";
    return o;
}


vector4::vector4()
{
}

vector4::vector4(scalar x, scalar y, scalar z, scalar w) : mX(x), mY(y), mZ(z), mW(w)
{
}

vector4::vector4(const vector4 & rhs) : mX(rhs.mX), mY(rhs.mY), mZ(rhs.mZ), mW(rhs.mW)
{
}

vector4 vector4::operator*(scalar rhs) const
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps1( &rhs );
    __m128 result = _mm_mul_ps(left, right);
    vector4 v;
    _mm_store_ps( &v.mX, result );

    return v;
#else
    return vector4( mX * rhs, mY * rhs, mZ * rhs, mW * rhs );
#endif
}

const vector4 & vector4::operator*=(scalar rhs)
{

#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps1( &rhs );
    __m128 result = _mm_mul_ps(left, right);
    _mm_store_ps( &mX, result );
#else
    mX *= rhs;
    mY *= rhs;
    mZ *= rhs;
    mW *= rhs;
#endif
    return *this;
}

vector4 vector4::operator/(scalar rhs) const
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps1( &rhs );
    __m128 result = _mm_div_ps(left, right);
    vector4 v;
    _mm_store_ps( &v.mX, result );

    return v;
#else
    return vector4( mX / rhs, mY / rhs, mZ / rhs, mW / rhs );
#endif
}

const vector4 & vector4::operator/=(scalar rhs)
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps1( &rhs );
    __m128 result = _mm_div_ps(left, right);
    _mm_store_ps( &mX, result );
#else
    mX /= rhs;
    mY /= rhs;
    mZ /= rhs;
    mW /= rhs;
#endif

    return *this;
}

vector4 vector4::operator+(const vector4 & rhs) const
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps( &rhs.mX );
    __m128 result = _mm_add_ps(left, right);
    vector4 v;
    _mm_store_ps( &v.mX, result );

    return v;
#else
    return vector4( mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ, mW + rhs.mW);
#endif
}

const vector4 & vector4::operator+=(const vector4 & rhs)
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps( &rhs.mX );
    __m128 result = _mm_add_ps(left, right);
    _mm_store_ps( &mX, result );
#else
    mX += rhs.mX;
    mY += rhs.mY;
    mZ += rhs.mZ;
    mW += rhs.mW;
#endif
    return *this;
}

vector4 vector4::operator-(const vector4 & rhs) const
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps( &rhs.mX );
    __m128 result = _mm_sub_ps(left, right);
    vector4 v;
    _mm_store_ps( &v.mX, result );

    return v;
#else
    return vector4( mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ, mW - rhs.mW);
#endif
}

const vector4 & vector4::operator-=(const vector4 & rhs)
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps( &rhs.mX );
    __m128 result = _mm_sub_ps(left, right);
    _mm_store_ps( &mX, result );
#else
    mX -= rhs.mX;
    mY -= rhs.mY;
    mZ -= rhs.mZ;
    mW -= rhs.mW;
#endif
    return *this;
}

scalar vector4::Dot(const vector4 & rhs) const
{
#ifdef OC_SIMD
    __m128 left = _mm_load_ps( &mX ); 
    __m128 right = _mm_load_ps( &rhs.mX );
    __m128 mult = _mm_mul_ps(left, right);
    mult = _mm_hadd_ps(mult, mult);
    mult = _mm_hadd_ps(mult, mult);
    scalar result;
    _mm_store_ss(&result, mult);
    return result;
#else
    return mX * rhs.mX + mY * rhs.mY + mZ * rhs.mZ + mW * rhs.mW;
#endif
}

scalar vector4::Length() const
{
    return sqrt(Dot(*this));
}

scalar vector4::Length2() const
{
    return Dot(*this);
}

const vector4 & vector4::Normalize()
{
    scalar l = Length();
    (*this) /= l;
    return (*this);
}
