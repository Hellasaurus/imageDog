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

    //typedef std::vector<RGB_24_c> rowVector;
    assert(di_header.depth == 24);

    iFile.seekg(bm_header.offset);

    std::vector<std::vector<RGB_24_c>> imgData = std::vector<std::vector<RGB_24_c>>(di_header.height, std::vector<RGB_24_c>(di_header.width, RGB_24_c {0}));
    
    for (std::vector<RGB_24_c> & row : imgData)
    {
        for (RGB_24_c & i : row) 
        {
            iFile >> i;
        }
    }

    
    std::ofstream oFile;
    oFile.open("test.bmp");
    
    di_header.img_size = di_header.depth * di_header.height * di_header.width;
    bm_header.size_of = di_header.img_size + bm_header.offset;

    oFile << bm_header << di_header;

    for (std::vector<RGB_24_c> & row : imgData)
    {
        for (RGB_24_c & i : row) 
        {
            oFile << i;
        }
    }

    oFile.close();
    

    return 0;
}