// BMP.cpp
#include "BMP.h"

#include <fstream>
#include <iostream>

BMP_Header & operator>>(std::ifstream & source, BMP_Header &op2)
{
    try
    {
        source >> op2.field[0];
        source >> op2.field[1];

        source >> op2.size_of;
        source >> op2.reserved;
        source >> op2.offset;
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return op2;
}

std::ostream &operator<<(std::ostream &op1, const BMP_Header &op2)
{
    op1 << "BMP Header: " << std::endl
        << "Header ID: " << op2.field[0] << op2.field[1] << std::endl
        << "Size of file: " << op2.size_of << std::endl
        << "Reserved: " << op2.reserved << std::endl
        << "Pixel Grid offset: 0x" << std::hex << op2.offset ;
    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const BMP_Header &op2)
{
    op1.write(&op2.field[0], 1);
    op1.write(&op2.field[1], 1);
    op1.write(reinterpret_cast<const char *> (&op2.size_of),  4);
    op1.write(reinterpret_cast<const char *> (&op2.reserved), 4);
    op1.write(reinterpret_cast<const char *> (&op2.offset),   4);
    return op1;
}

DIB_Header & operator>>(std::ifstream &source, DIB_Header &op2)
{
    try 
    {
        source >> op2.header_size;
        source >> op2.width;      
        source >> op2.height;     

        source >> op2.color_planes;
        source >> op2.depth;       

        source >> op2.compression_type;
        source >> op2.img_size;       
        source >> op2.h_resolution;   
        source >> op2.v_resolution;   
        source >> op2.colors;         
        source >> op2.important;      
        /*
        op2.header_size = extract_uint32(source);
        op2.width       = extract_uint32(source);
        op2.height      = extract_uint32(source);

        op2.color_planes = extract_uint16(source);
        op2.depth        = extract_uint16(source);

        op2.compression_type = extract_uint32(source);
        op2.img_size        = extract_uint32(source);
        op2.h_resolution    = extract_int32(source);
        op2.v_resolution    = extract_int32(source);
        op2.colors          = extract_uint32(source);
        op2.important       = extract_uint32(source);
        */
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return op2;
}

std::ostream &operator<<(std::ostream &op1, const DIB_Header &op2)
{
    op1 << "DIB Header:" << std::endl
        << "Header Size: " << std::dec << op2.header_size << std::endl
        << "Image w x h: " << op2.width << " x " << op2.height << std::endl
        << "Color Planes: " << op2.color_planes << std::endl
        << "Bit depth: " << op2.depth << std::endl
        << "Compression: " << op2.compression_type << std::endl
        << "sizeOf img data: 0x" << std::hex << op2.img_size << std::endl
        << "Resolution, px/m: 0x" << std::hex << op2.h_resolution << "h x 0x" << std::hex << op2.v_resolution << "w"<< std::endl
        << "Colors: " << op2.colors << std::endl
        << "Important colors: 0x" << std::hex << op2.important;
    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const DIB_Header &op2)
{
    op1.write(reinterpret_cast<const char *>(&op2.header_size), sizeof(op2.header_size));
    op1.write(reinterpret_cast<const char *>(&op2.width), sizeof(op2.width));
    op1.write(reinterpret_cast<const char *>(&op2.height), sizeof(op2.height));
    op1.write(reinterpret_cast<const char *>(&op2.color_planes), sizeof(op2.color_planes));
    op1.write(reinterpret_cast<const char *>(&op2.depth), sizeof(op2.depth));
    op1.write(reinterpret_cast<const char *>(&op2.compression_type), sizeof(op2.compression_type));
    op1.write(reinterpret_cast<const char *>(&op2.img_size), sizeof(op2.img_size));
    op1.write(reinterpret_cast<const char *>(&op2.h_resolution), sizeof(op2.h_resolution));
    op1.write(reinterpret_cast<const char *>(&op2.v_resolution), sizeof(op2.v_resolution));
    op1.write(reinterpret_cast<const char *>(&op2.colors), sizeof(op2.colors));
    op1.write(reinterpret_cast<const char *>(&op2.important), sizeof(op2.important));

    return op1;
}

std::ifstream &operator>>(std::ifstream &op1, uint16_t &op2)
{
    char a = op1.get();
    char b = op1.get();

    op2 = ( 0xFF & a) | ( 0xFF & b) << 8;
    return op1;
}

uint16_t extract_uint16(std::ifstream &source)
{
    char a = source.get();
    char b = source.get();

    return ( 0xFF & a) | ( 0xFF & b) << 8;
}

std::ifstream &operator >>(std::ifstream &op1, RGB_24_c &op2)
{
    op2.color[0] = MASK & op1.get();
    op2.color[1] = MASK & op1.get();
    op2.color[2] = MASK & op1.get();

    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const RGB_24_c &op2)
{
    const char * head = reinterpret_cast<const char*> (&op2.color);
    op1.write(head, 3);
    return op1;
}

std::ifstream &operator>>(std::ifstream &op1, uint32_t &op2)
{
    op1.read(reinterpret_cast<char*>(&op2), 4);
    return op1;
}

uint32_t extract_uint32(std::ifstream &source)
{
    char a = source.get();
    char b = source.get();
    char c = source.get();
    char d = source.get();

    return ( 0xFF & a) | ( 0xFF & b) << 8 | ( 0xFF & c) << 16 | (0xFF & d) << 24 ;
}

std::ifstream &operator>>(std::ifstream &op1, int32_t &op2)
{
    char a = op1.get();
    char b = op1.get();
    char c = op1.get();
    char d = op1.get();

    op2 = ( 0xFF & a) | ( 0xFF & b) << 8 | ( 0xFF & c) << 16 | (0xFF & d) << 24 ;
    return op1;
}


int32_t extract_int32(std::ifstream &source)
{
    char a = source.get();
    char b = source.get();
    char c = source.get();
    char d = source.get();

    return ( 0xFF & a) | ( 0xFF & b) << 8 | ( 0xFF & c) << 16 | (0xFF & d) << 24 ;
}
