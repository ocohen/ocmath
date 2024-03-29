#include <vector4.hpp>
#include <iostream>
#include <cmath>
#include <simd.hpp>

using namespace oc;

//make it nice to print to screen
std::ostream & operator<<(std::ostream & o, const oc::vector4 & rhs)
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
    SIMDV(left, *this);
    __m128 right = _mm_load_ps1( &rhs );
    vector4 v;
    SIMDV(result, v);
    *result = _mm_mul_ps(*left, right);

    return v;
#else
    return vector4( mX * rhs, mY * rhs, mZ * rhs, mW * rhs );
#endif
}

const vector4 & vector4::operator*=(scalar rhs)
{

#ifdef OC_SIMD
    SIMDV(left, *this);
    __m128 right = _mm_load_ps1( &rhs );
    *left = _mm_mul_ps(*left, right);
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
    SIMDV(left, *this);
    __m128 right = _mm_load_ps1( &rhs );
    vector4 v;
    SIMDV(result, v);
    *result = _mm_div_ps(*left, right);
    return v;
#else
    return vector4( mX / rhs, mY / rhs, mZ / rhs, mW / rhs );
#endif
}

const vector4 & vector4::operator/=(scalar rhs)
{
#ifdef OC_SIMD
    SIMDV(left, *this);
    __m128 right = _mm_load_ps1( &rhs );
    *left = _mm_div_ps(*left, right);
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
    SIMDV(left, *this);
    SIMDV(right, rhs);
    vector4 v;
    SIMDV(result, v);
    *result = _mm_add_ps(*left, *right);
    return v;
#else
    return vector4( mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ, mW + rhs.mW);
#endif
}

const vector4 & vector4::operator+=(const vector4 & rhs)
{
#ifdef OC_SIMD
    SIMDV(left, *this);
    SIMDV(right, rhs);
    *left = _mm_add_ps(*left, *right);
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
    SIMDV(left, *this);
    SIMDV(right, rhs);
    vector4 v;
    SIMDV(result, v);
    *result = _mm_sub_ps(*left, *right);

    return v;
#else
    return vector4( mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ, mW - rhs.mW);
#endif
}

vector4 vector4::operator-() const
{
    return vector4( -mX, -mY, -mZ, -mW );
}

const vector4 & vector4::operator-=(const vector4 & rhs)
{
#ifdef OC_SIMD
    SIMDV(left, *this);
    SIMDV(right, rhs);
    *left = _mm_sub_ps(*left, *right);
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
    SIMDV(left, *this);
    SIMDV(right, rhs);
    __m128 mult = _mm_mul_ps(*left, *right);
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

vector4 vector4::GetNormalized() const
{
    scalar l = Length();
    return *this / l;
}

const vector4 &  vector4::operator=(const vector4 & rhs)
{
    mX = rhs.mX;
    mY = rhs.mY;
    mZ = rhs.mZ;
    mW = rhs.mW;
}
