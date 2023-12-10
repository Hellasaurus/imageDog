// bmpread.cpp
#include "BMPread.h"
#include "BMPencode.h"

#include <fstream>
#include <iostream>

BMP_Header get_BMP_header(std::ifstream &source)
{
    BMP_Header out = BMP_Header();
    try
    {
        source >> out.field[0];
        source >> out.field[1];

        out.size_of = extract_uint32(source);

        out.reserved = extract_uint32(source);

        out.offset = extract_uint32(source);
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return out;
}

std::ostream &operator<<(std::ostream &op1, const BMP_Header &op2)
{
    op1 << "BMP Header: " << std::endl
        << "Header ID: " << op2.field[0] << op2.field[1] << std::endl
        << "Size of file: " << op2.size_of << std::endl
        << "Reserved: " << op2.reserved << std::endl
        << "Pixel Grid offset: " << op2.offset ;
    return op1;
}

DIB_Header get_DIB_header(std::ifstream &source)
{
    DIB_Header out = DIB_Header();

    try 
    {

        out.header_size = extract_uint32(source);
        out.width = extract_uint32(source);
        out.height = extract_uint32(source);

        out.color_planes = extract_uint16(source);
        out.depth = extract_uint16(source);

        out.compression_type = extract_uint32(source);
        out.img_size = extract_uint32(source);
        out.h_resolution = extract_int32(source);
        out.v_resolution = extract_int32(source);
        out.colors = extract_uint32(source);
        out.important = extract_uint32(source);
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return out;
}

std::ostream &operator<<(std::ostream &op1, const DIB_Header &op2)
{
    op1 << "DIB Header:" << std::endl
        << "Header Size: " << op2.header_size << std::endl
        << "Image w x h: " << op2.width << " x " << op2.height << std::endl
        << "Color Planes: " << op2.color_planes << std::endl
        << "Bit depth: " << op2.depth << std::endl
        << "Compression: " << op2.compression_type << std::endl
        << "sizeOf img data: " << std::hex << op2.img_size << std::endl
        << "Resolution, px/m:" << std::hex << op2.h_resolution << "h x " << std::hex << op2.v_resolution << "w"<< std::endl
        << "Colors: " << op2.colors << std::endl
        << "Important colors: " << std::hex << op2.important;
    return op1;
}

uint16_t extract_uint16(std::ifstream &source)
{
    char a; char b ;

    source >> a;
    source >> b;

    uint16_t out = (0x00FF & b);
    out = (out << 8) | (0x00FF & a);
    return out;
}

uint32_t extract_uint32(std::ifstream &source)
{
    char a; char b ; char c ; char d;

    source >> a;
    source >> b;
    source >> c;
    source >> d;

    uint32_t out = (0x000000FF & d);
    out = (out << 8) | (0x000000FF & c);
    out = (out << 8) | (0x000000FF & b);
    out = (out << 8) | (0x000000FF & a);
    return out;
}

int32_t extract_int32(std::ifstream &source)
{
    char a; char b ; char c ; char d;

    source >> a;
    source >> b;
    source >> c;
    source >> d;

    int32_t out = (0x000000FF & d);
    out = (out << 8) | (0x000000FF & c);
    out = (out << 8) | (0x000000FF & b);
    out = (out << 8) | (0x000000FF & a);
    return out;
}
