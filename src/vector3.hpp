#ifndef OC_VECTOR3_H
#define OC_VECTOR3_H

#include <vector4.hpp>

namespace oc
{

class vector3 : public vector4
{
public:
    vector3();
    vector3(scalar x, scalar y, scalar z);
    vector3( const vector4 & rhs );

    vector3 Cross(const vector3 & rhs ) const;

};

}
#endif
