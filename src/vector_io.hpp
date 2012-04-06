#ifndef OC_VECTOR_IO_H
#define OC_VECTOR_IO_H

#include <iostream>

namespace ocmath
{
class vector4;
}

std::ostream & operator<<(std::ostream & o, const ocmath::vector4 & rhs);
#endif
