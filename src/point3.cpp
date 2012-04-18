#include <point3.hpp>
#include <vector_io.hpp>

using namespace oc;

std::ostream & operator<<(std::ostream & o, const oc::point3 & rhs)
{
    o << "(" << rhs.X() << "," << rhs.Y() << "," << rhs.Z() << ")";
    return o;
}

point3::point3(){}

point3::point3(scalar x, scalar y, scalar z) : vector4(x, y, z, 1.0){}

point3::point3(const vector4 & rhs) : vector4( rhs.X(), rhs.Y(), rhs.Z(), 1.0){}

vector3 point3::operator-(const point3 & rhs) const
{
    return vector3( vector4::operator-(rhs) );
}

point3 point3::operator-() const
{
    return point3(-mX, -mY, -mZ);
}
