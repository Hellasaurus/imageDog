// main.cpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

#include "BMP.h"

 

int main() {
    std::string path = "test_24_bit_padding.bmp";

    BitMap myBitmap= BitMap(path);

    std::ofstream oFile;
    oFile.open("test.bmp");

    oFile << myBitmap;
    oFile.close();

    return 0;

}