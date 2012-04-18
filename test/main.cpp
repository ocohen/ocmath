#include <vector.hpp>
#include <matrix.hpp>
#include <transform.hpp>
#include <iostream>
#include <octimer.hpp>
#include <quaternion.hpp>

using namespace oc;

int main()
{
    Transform Move = Matrix::Identity();
    Transform T = Matrix::Identity();
	point3 origin(10,10,0);
    Move.SetOrigin(origin);
    point3 lookAt(0,0,0);
    vector3 up(0,1,0);
	//std::cout << "origin: " << origin << std::endl;
	vector3 dir = lookAt - origin;
	//std::cout << "dir: " << dir << std::endl;
	dir.Normalize();
	//std::cout << "dir normalized: " << dir << std::endl;
	vector3 lat = up.Cross(dir);
	lat.Normalize();
	//std::cout << "lat: " << lat << std::endl;

	vector3 cameraUp = dir.Cross(lat);
	cameraUp.Normalize();
	//std::cout << "cameraUp: " << cameraUp << std::endl;

	//now put origin back in
	//lat.mData[3] = lat.Dot(origin);
	//cameraUp.mData[3] = cameraUp.Dot(origin);
	//dir.mData[3] = dir.Dot(origin);


    T.SetRow(0, lat);
    T.SetRow(1, cameraUp);
    T.SetRow(2, dir);

    std::cout << "T: " << T << std::endl;
    std::cout << "Move: " << Move << std::endl;

    T = T*Move;
    std::cout << "T * M " << T << std::endl;

    point3 test(0,0,0);
    
    std::cout << "World space: " << test << std::endl;

    std::cout << "Camera space: " << T * test << std::endl;


#if 0
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

    l = l - m;

    std::cout << l << std::endl;

    point3 p(1,2,3);

    vector4 p2 = p;
    std::cout << "p " << p << std::endl;
    std::cout << "p2 " << p2 << std::endl;

    Matrix mat = Matrix::Identity();
    std::cout << "mat : " << mat << std::endl;
    vector4 t(1,2,3,4);

    float data[16] = {  1, 0, 0, 1,
                        0, 0, 1, 0,
                        0, 1, 0, 0,
                        0, 0, 0, 0 };

    Matrix mat2( data );
    std::cout << "mat2 " << mat2 << std::endl;

    std::cout << "mat2 * t = " << mat2 * t << std::endl;

    float data2[16] = {  1, 2, 3, 0,
                        5, 6, 7, 0,
                        9, 10, 11, 0,
                        13, 14, 15, 1 };

    Matrix mat3( data2 );
    Matrix mat4( data2 );

    std::cout << "mat3 " << mat3 << std::endl;
    std::cout << "mat2 * mat3 " << mat2 * mat3 << std::endl;

    oc::Timer timer;
    for(int i=0; i<300000; i++)
    {
        t = mat2 * t;
    }

    std::cout << "Time elapsed: " << timer.GetMicroseconds() << std::endl;

    std::cout << t << std::endl;

    timer.Restart();
    for(int i=0; i<30000; i++)
    {
        mat4 = mat4 * mat3;
        if( i % 11 == 0)
        {
            mat4 = mat3;
        }
    }
    std::cout << mat4 << std::endl;
    std::cout << "Time elapsed: " << timer.GetMicroseconds() << std::endl;

    Transform trans(data2);
    Transform trans2(data2);
    Transform t3(data2);
    timer.Restart();
    for(int i=0; i<30000; i++)
    {
        t3 = t3 * trans;
        if( i % 11 == 0)
        {
            t3 = trans2;
        }
    }
    std::cout << t3 << std::endl;
    std::cout << "Time elapsed: " << timer.GetMicroseconds() << std::endl;

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

    vector3 v(1, 0, 0);
    Quaternion q = Quaternion::FromAxis(3.14159 / 4, vector3(0,1,1)); 
    std::cout << "q " << q << std::endl;
    std::cout << "q * v = " << q * v << std::endl;

    return 0;
}

Matrix Quaternion::GetMatrix() const
{
    scalar x = mAxis.X();
    scalar y = mAxis.Y();
    scalar z = mAxis.Z();

    scalar x2 = x*x;
    scalar y2 = y*y;
    scalar z2 = z*z;
    scalar xy = x*y;
    scalar xz = x*z;
    scalar yz = y*z;
    scalar wx = mW*x;
    scalar wy = mW*y;
    scalar wz = mW*z;

    //got the formula from here:
    //http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation

    scalar data[16] = {1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
                       2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
                       2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f};
    return Matrix(data);
}
