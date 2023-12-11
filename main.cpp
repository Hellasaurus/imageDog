// main.cpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#include "BMP.h"

 

int main()
{
    std::ifstream iFile;

    std::string path = "test_24_bit.bmp";

    iFile.open(path);

    BMP_Header bm_header;//= get_BMP_header(iFile);
    DIB_Header di_header;//= get_DIB_header(iFile);

    iFile >> bm_header;
    iFile >> di_header;

    int img_height = di_header.height;
    int img_width  = di_header.width;

    typedef std::vector<RGB_24_c> rowVector;
    assert(di_header.depth == 24);
    
    unsigned int rawSize = img_width * di_header.depth;
    unsigned int pad = rawSize % 4;
    unsigned int rowSize = rawSize + pad;

    std::vector<rowVector> imgData = std::vector<rowVector>( img_height, rowVector(rowSize));

    unsigned int i = 0;
    unsigned int p = 0;
    int step = di_header.depth >> 3;
    iFile.seekg(bm_header.offset);
    while (i < di_header.img_size)
    {
        int r = p/rowSize;
        int c = p % rowSize;
        imgData[r][c] = extract_RGB24(iFile);
        i += step;
        p = i/3;
    }

    std::cout << bm_header << std::endl << di_header;

    iFile.close();

    std::ofstream oFile;
    path = "test.bmp";
    oFile.open(path);

    oFile << bm_header << di_header;

    i = 0;
    unsigned int end = bm_header.size_of;
    while (i < end)
    {
        RGB_24_c temp = imgData[i/rowSize][i % rowSize];
        oFile << temp;
        i = oFile.tellp();
    }

    oFile.close();
    

    return 0;
}