// main.cpp

#include <string>
#include <iostream>
#include <fstream>

#include "BMPread.h"
#include "BMPencode.h"


int main()
{
    std::ifstream file;

    std::string path = "grass.bmp";

    file.open(path);

    BMP_Header bm_header = get_BMP_header(file);
    DIB_Header di_header = get_DIB_header(file);

    std::cout << bm_header << std::endl << di_header;

    return 0;
}