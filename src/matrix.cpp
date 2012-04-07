#include <matrix.hpp>

using namespace ocmath;

//Assuming row major
#define DataFrom(array, row, col) array[row * 4 + col]
#define Data(row,col) DataFrom(mData, row, col)


std::ostream & operator<<(std::ostream & o, const ocmath::Matrix & rhs)
{
    const float * mData = rhs.GetData();    //only calling it mData for the sake of the macro
    o << std::endl;
    o << "[ " << Data(0,0) << "," << Data(0,1) << "," << Data(0,2) << "," << Data(0,3) << std::endl;
    o << "  " << Data(1,0) << "," << Data(1,1) << "," << Data(1,2) << "," << Data(1,3) << std::endl;
    o << "  " << Data(2,0) << "," << Data(2,1) << "," << Data(2,2) << "," << Data(2,3) << std::endl;
    o << "  " << Data(3,0) << "," << Data(3,1) << "," << Data(3,2) << "," << Data(3,3) << " ]" << std::endl;
    return o;
}

Matrix::Matrix(scalar * data)
{
    for(int i=0; i<16; i++)
    {
        mData[i] = data[i];
    }
}

Matrix Matrix::Identity()
{
    scalar data[] = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 1.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 1.0f};
    return Matrix(data);
}

vector4 Matrix::GetColumn(int index)
{
    int c1 = Data(0, index);
    int c2 = Data(1, index);
    int c3 = Data(2, index);
    int c4 = Data(3, index);
    return vector4( mData[c1], mData[c2], mData[c3], mData[c4] ); 
}

vector4 Matrix::GetRow(int index)
{
    int c1 = Data(index, 0);
    int c2 = Data(index, 1);
    int c3 = Data(index, 2);
    int c4 = Data(index, 3);
    return vector4( mData[c1], mData[c2], mData[c3], mData[c4] ); 
}

vector4 Matrix::operator*(const vector4 & X)
{
    float x = X.X() * Data(0,0) + X.Y() * Data(0, 1) + X.Z() * Data(0, 2) + X.W() * Data(0, 3);
    float y = X.X() * Data(1,0) + X.Y() * Data(1, 1) + X.Z() * Data(1, 2) + X.W() * Data(1, 3);
    float z = X.X() * Data(2,0) + X.Y() * Data(2, 1) + X.Z() * Data(2, 2) + X.W() * Data(2, 3);
    float w = X.X() * Data(3,0) + X.Y() * Data(3, 1) + X.Z() * Data(3, 2) + X.W() * Data(3, 3);

    return vector4(x,y,z,w);
}

Matrix Matrix::operator*(const Matrix & rhs)
{
    float output[16];
    const float * data = rhs.GetData();
    
    for(int c = 0; c<4; ++c)
    {
        for(int r = 0; r < 4; ++r)
        {
            DataFrom(output, r, c) = Data(r,0) * DataFrom(data, 0,c) + Data(r, 1) * DataFrom(data, 1,c) + Data(r,2) * DataFrom(data, 2, c) + Data(r,3) * DataFrom(data, 3, c);
        }
    }

    return Matrix(output);
}
#undef Data(row, col)
#undef DATA(array, row, col)
