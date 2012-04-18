#include <quaternion.hpp>
#include <iostream>
#include <cmath>

using namespace oc;

std::ostream & operator<<(std::ostream & o, const oc::Quaternion & rhs)
{
    o << rhs.W() << " + " << rhs.Axis();
    return o;
}

Quaternion Quaternion::FromAxis(scalar angle, vector3 axis)
{
    angle *= 0.5f;
    return Quaternion( cos(angle), sin(angle) * axis.Normalize() );
}

Quaternion::Quaternion(scalar angle, const vector3 & v) : mW(angle), mAxis(v)
{
}

scalar Quaternion::Length2() const
{
    return mW * mW + mAxis.Length2();
}

scalar Quaternion::Length() const
{
    return sqrt(mW*mW + mAxis.Length2());
}

const Quaternion & Quaternion::Normalize()
{
    scalar length = Length();
    mW /= length;
    mAxis /= length;
    return *this;
}

Quaternion Quaternion::operator*(const Quaternion & rhs) const
{
    scalar w = mW * rhs.mW - mAxis.Dot(rhs.mAxis);
    vector3 v = mW * rhs.mAxis + rhs.mW * mAxis + (mAxis.Cross(rhs.mAxis));
    
    return Quaternion(w, v);
}

const Quaternion & Quaternion::operator*=(const Quaternion & rhs)
{
    scalar w = mW * rhs.mW - mAxis.Dot(rhs.mAxis);
    vector3 v = mW * rhs.mAxis + rhs.mW * mAxis + (mAxis.Cross(rhs.mAxis));

    mW = w;
    mAxis = v;
    
    return *this; 
}

Quaternion Quaternion::GetConjugate() const
{
    return Quaternion(mW, -mAxis);
}

vector3 Quaternion::operator*(const vector3 & rhs) const
{
    Quaternion vec(0, rhs.GetNormalized() );
    Quaternion res = *this * vec * GetConjugate();
    return res.Axis();
}
