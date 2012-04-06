#include <vector4.hpp>
#include <iostream>
#include <cmath>

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
    return vector4( mX * rhs, mY * rhs, mZ * rhs, mW * rhs );
}

const vector4 & vector4::operator*=(scalar rhs)
{
    mX *= rhs;
    mY *= rhs;
    mZ *= rhs;
    mW *= rhs;

    return *this;
}

vector4 vector4::operator/(scalar rhs) const
{
    return vector4( mX / rhs, mY / rhs, mZ / rhs, mW / rhs );
}

const vector4 & vector4::operator/=(scalar rhs)
{
    mX /= rhs;
    mY /= rhs;
    mZ /= rhs;
    mW /= rhs;

    return *this;
}

vector4 vector4::operator+(const vector4 & rhs) const
{
    return vector4( mX + rhs.mX, mY + rhs.mY, mZ + rhs.mZ, mW + rhs.mW);
}

const vector4 & vector4::operator+=(const vector4 & rhs)
{
    mX += rhs.mX;
    mY += rhs.mY;
    mZ += rhs.mZ;
    mW += rhs.mW;
    return *this;
}

vector4 vector4::operator-(const vector4 & rhs) const
{
    return vector4( mX - rhs.mX, mY - rhs.mY, mZ - rhs.mZ, mW - rhs.mW);
}

const vector4 & vector4::operator-=(const vector4 & rhs)
{
    mX -= rhs.mX;
    mY -= rhs.mY;
    mZ -= rhs.mZ;
    mW -= rhs.mW;
    return *this;
}

scalar vector4::Dot(const vector4 & rhs) const
{
    return mX * rhs.mX + mY * rhs.mY + mZ * rhs.mZ + mW * rhs.mW;
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
