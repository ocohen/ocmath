#ifndef OC_MATRIX_H
#define OC_MATRIX_H

#include <simd.hpp>
#include <vector.hpp>

namespace oc
{

class Matrix
{
public:

    Matrix(scalar * data);

    static Matrix Identity();

    vector4 operator*(const vector4 & rhs) const;   
    Matrix operator*(const Matrix & rhs) const;
    
    vector4 GetColumn(int index);
    vector4 GetRow(int index);
    const float * GetData() const {return mData;}

private:
    scalar mData[16] OC_ALIGN;


};

}

#endif
