#ifndef OC_MATRIX_H
#define OC_MATRIX_H

#include <simd.hpp>
#include <vector.hpp>

namespace oc
{

class Matrix
{
public:

    Matrix(){}
    Matrix(scalar * data);
    Matrix(const Matrix & rhs);

    static Matrix Identity();

    vector4 operator*(const vector4 & rhs) const;   
    Matrix operator*(const Matrix & rhs) const;
    
    vector4 GetColumn(int index);
    vector4 GetRow(int index);
    const float * GetData() const {return mData;}

protected:  //protected so extended class can use SIMD operations on data
    scalar mData[16] OC_ALIGN;


};

}
#define DataFrom(array, major, minor) array[major * 4 + minor]
#define Data(major,minor) DataFrom(mData, major, minor)

#endif
