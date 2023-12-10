// bmpread.cpp
#include "BMPread.h"
#include "BMPencode.h"

#include <fstream>
#include <iostream>

BMP_Header get_BMP_header(std::fstream &source)
{
    BMP_Header out;
    try
    {
        source >> out.field[0];
        source >> out.field[1];

        char a; char b; char c; char d;
        source >> a, b, c, d ;
        out.size_of = char_to_uint16(a,b,c,d);

        source >> a, b, c, d ;
        out.reserved = char_to_uint16(a,b,c,d);

        source >> out.offset;
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return out;
}

DIB_Header get_DIB_header(std::fstream &source)
{
    return DIB_Header();
}

uint16_t char_to_uint16(char a, char b, char c, char d)
{
    uint16_t out = a;
    out = (out << 8) + b;
    out = (out << 8) + c;
    out = (out << 8) + d;
    return out;
}
