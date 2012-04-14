#include <ocmath.hpp>
#include <cmath>

namespace oc
{

bool Epsilon(scalar x, scalar y)
{
    return fabs( y - x ) < 1e-16;
}

}
