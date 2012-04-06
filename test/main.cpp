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

    vector3 v(1,2,3);
    std::cout << "v :" << v << std::endl;
    std::cout << "v + (1,1,1,1): " << v + vector4(1,1,1,1) << std::endl;

    vector3 i(1,0,0);
    vector3 j(0,1,0);
    vector3 k = i.Cross(j);

    std::cout << i << " x " << j << " = " << k << std::endl;
    std::cout << j << " x " << i << " = " << j.Cross(i) << std::endl;
    std::cout << i << " x " << i << " = " << i.Cross(i) << std::endl;

    vector3 l(1, 0, 0);
    vector3 m(1, 1, 0);

    std::cout << l << " x " << m << " = " << l.Cross(m) << std::endl;

#if 0
    vector3 a(1,2,3);
    vector3 b(2,3,4);
    vector3 c;
    for(int i=0; i< 100000000; i++)
    {
        a *= 3.5;
        b += a;
        b /= 2.0;

        if(a.Length() > 1000)
        {
            a = vector3(1, 2, 3);
        }

        c = a.Cross(b);
    }
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
#endif

    return 0;
}
