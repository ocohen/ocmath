#ifndef OC_QUATERNION_H
#define OC_QUATERNION_H

#include <vector.hpp>

namespace oc
{

class Quaternion
{
public:
    Quaternion(){}
    Quaternion(scalar w, const vector3 & axis);

    static Quaternion FromAxis(scalar w, vector3 axis);

    scalar W() const { return mW; }
    scalar Angle() const { return mW; }
    const vector3 & Axis() const { return mAxis; }

    scalar Length() const;
    scalar Length2() const;
    const Quaternion & Normalize();

    Quaternion operator*(const Quaternion & rhs) const;
    const Quaternion & operator*=(const Quaternion & rhs);
    vector3 operator*(const vector3 & rhs) const;

    Matrix GetMatrix() const;

private:

    Quaternion GetConjugate() const;

    scalar mW OC_ALIGN;
    vector3 mAxis;
};

}
#endif
