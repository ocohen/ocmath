#ifndef OC_VECTOR4_H
#define OC_VECTOR4_H

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

private:
    scalar mX, mY, mZ, mW;
};

    inline vector4 operator*(scalar lhs, const vector4 & rhs) { return rhs * lhs; }


}

#endif