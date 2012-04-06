#ifndef OC_POINT3
#define OC_POINT3

#include <vector4.hpp>
#include <vector3.hpp>

namespace ocmath
{

class point3 : public vector4
{
public:
    point3();
    point3(scalar x, scalar y, scalar z);
    point3(const point3 & rhs);

    vector3 operator-(const point3 & rhs);

private:    //all of these operations are undefined for a point3
    point3 operator+(const point3 & rhs) const;
    const point3 & operator+=(const point3 & rhs);

    const point3 & operator-=(const point3 & rhs);

    point3 operator*(scalar k) const;
    point3 operator*=(scalar k);

    point3 operator/(scalar k) const;
    point3 operator/=(scalar k);

};

    point3 operator*(scalar lhs, const point3 & rhs);  //DON'T implement this. This is going to not link on purpose, the operation is undefined for a point3
}
#endif