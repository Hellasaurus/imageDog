// main.cpp

#include <string>
#include <iostream>
#include <fstream>

#include "BMPread.h"
#include "BMPencode.h"


int main()
{
    std::fstream file;

    std::string path = "grass.bmp";

    file.open(path, std::fstream::in);

    BMP_Header header = get_BMP_header(file);

    std::cout 
        << header.field[0] << header.field[1] << std::endl
        << header.size_of << std::endl
        << header.reserved << std::endl
        << header.offset << std::endl;

    return 0;
}