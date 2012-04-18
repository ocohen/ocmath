#ifndef OC_VECTOR_IO_H
#define OC_VECTOR_IO_H

#include <iostream>

namespace oc
{
class vector4;
class vector3;
class Quaternion;
class Matrix;
}

std::ostream & operator<<(std::ostream & o, const oc::vector4 & rhs);
std::ostream & operator<<(std::ostream & o, const oc::vector3 & rhs);
std::ostream & operator<<(std::ostream & o, const oc::point3 & rhs);
std::ostream & operator<<(std::ostream & o, const oc::Quaternion & rhs);
std::ostream & operator<<(std::ostream & o, const oc::Matrix & rhs);
#endif
