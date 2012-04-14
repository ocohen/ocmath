#ifndef OC_TRANSFORM_H
#define OC_TRANSFORM_H

#include <matrix.hpp>

namespace oc
{

class Transform : public Matrix
{
public:
    Transform(){}
    Transform(scalar * data);   //Note that since this is a transform. Positions 3, 7, 11 and 15 are (0,0,0,1) regardless of input. Origin is at position 12, 13, 14 
    Transform(const Matrix & rhs);
    Transform(const Transform & rhs);
    Transform operator*(const Transform & rhs) const;

};
}
#endif
