// BMP.tpp
// BMP template implementations

#include "BMP.h"
#include <vector>

template <typename TYPE>
PixelArray<TYPE>::PixelArray(int w, int h, char pad) 
{
    typedef std::vector<TYPE> rowVector;
    data = std::vector<rowVector>(w, rowVector(h, TYPE()));
    padding = pad;
}