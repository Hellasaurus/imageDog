// BMP.tpp
// BMP template implementations

#include "BMP.h"
#include <vector>


template<typename TYPE>
PixelArray<TYPE>::PixelArray(int h, int w) : 
    data(std::vector<std::vector<TYPE>>(h,std::vector<TYPE>(w, TYPE {0}))), 
    rows(h), 
    cols(w)
{}

template <typename TYPE>
std::ofstream &operator<<(std::ofstream &op1, const PixelArray<TYPE> &op2)
{
    long pos = op1.tellp();
    for (int r = 0; r < op2.rows; r++)
    {
        for (int c = 0; c < op2.cols; c++)
        {
            op1 << op2.data[r][c];
        }
        unsigned char padding = op1.tellp() - pos % 4;
        while (padding)
        {
            op1 << "\0";
            padding--;
        }

    }
    return op1;
}

template<typename TYPE>
std::ifstream & operator>>(std::ifstream & op1, PixelArray<TYPE>& op2)
{
    std::vector<TYPE> row;
    for (int r = 0; r < op2.rows; r++)
    {
        for (int c = 0; c < op2.cols; c++)
        {
            op1 >> op2.data[r][c];
        }
    }
    return op1;
}