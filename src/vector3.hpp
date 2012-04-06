#ifndef OC_VECTOR3_H
#define OC_VECTOR3_H

#include <vector4.hpp>

namespace ocmath
{

class vector3 : public vector4
{
public:
    vector3();
    vector3(float x, float y, float z);
    vector3( const vector3 & rhs );

    vector3 Cross(const vector3 & rhs ) const;

};

}
#endif
