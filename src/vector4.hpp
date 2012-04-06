#ifndef OC_VECTOR4_H
#define OC_VECTOR4_H

#include <simd.hpp>

namespace ocmath
{

typedef float scalar;

class vector4
{
public:
    vector4();
    vector4(scalar x, scalar y, scalar z, scalar w);
    vector4(const vector4 & rhs);

    vector4 operator+(const vector4 & rhs) const;
    const vector4 & operator+=(const vector4 & rhs);

    vector4 operator-(const vector4 & rhs) const;
    const vector4 & operator-=(const vector4 & rhs);

    vector4 operator*(scalar rhs) const;
    const vector4 & operator*=(scalar rhs);

    vector4 operator/(scalar rhs) const;
    const vector4 & operator/=(scalar rhs);

    scalar X() const { return mX; }
    scalar Y() const { return mY; }
    scalar Z() const { return mZ; }
    scalar W() const { return mW; }

    scalar Length() const;
    scalar Length2() const;

    scalar Dot(const vector4 & rhs) const;

    const vector4 & Normalize();

    const vector4 & operator=(const vector4 & rhs);

protected:
    scalar mX OC_ALIGN;
    scalar mY, mZ, mW;   //this is protected because anyone extending this will want to use data directly for SIMD type instructions.

};

    inline vector4 operator*(scalar lhs, const vector4 & rhs) { return rhs * lhs; }


}

#ifdef OC_SIMD
#define SIMDV(name, vector) __m128 * name = (__m128*) &(vector).mX
#endif

#endif
