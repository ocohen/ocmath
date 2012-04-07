#ifndef OC_VECTOR_IO_H
#define OC_VECTOR_IO_H

#include <iostream>

namespace ocmath
{
class vector4;
class vector3;
class Matrix;
}

std::ostream & operator<<(std::ostream & o, const ocmath::vector4 & rhs);
std::ostream & operator<<(std::ostream & o, const ocmath::vector3 & rhs);
std::ostream & operator<<(std::ostream & o, const ocmath::point3 & rhs);
std::ostream & operator<<(std::ostream & o, const ocmath::Matrix & rhs);
#endif
