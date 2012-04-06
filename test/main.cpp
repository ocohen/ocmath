#include <vector.hpp>
#include <iostream>

using namespace ocmath;

int main()
{
    vector4 f(1,2,3,4);
    vector4 g = f;
    vector4 s;

    vector4 w = f * 2;
    vector4 d = 2 * f;

    std::cout << "f: " << f << std::endl;
    std::cout << "g: " << g << std::endl;
    std::cout << "s: " << s << std::endl;
    std::cout << "w: " << w << std::endl;
    std::cout << "d: " << d << std::endl;

    w *= 2;

    std::cout << "w: " << w << std::endl;

    vector4 e = d / 2;
    std::cout << "e: " << e << std::endl;

    e /= 2;
    std::cout << "e: " << e << std::endl;

    std::cout << "f + g " << (f+g) << std::endl;
    std::cout << "f - g " << (f-g) << std::endl;

    f += g;

    std::cout << "f :" << f << std::endl;

    w -= g;
    std::cout << "w :" << w << std::endl;

    std::cout << "f dot g " << (f.Dot(g)) << std::endl;
    std::cout << "f Length " << (f.Length()) << std::endl;
    std::cout << "f Length2 " << (f.Length2()) << std::endl;
    std::cout << "f normal" << f.Normalize() << std::endl;
    std::cout << "f: " << f << std::endl;

    return 0;
}