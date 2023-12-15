// BMP.cpp
#include "BMP.h"

#include <fstream>
#include <iostream>
#include <assert.h>
#include <cmath>
#include <cstring>

std::ifstream & operator>>(std::ifstream & source, BMP_Header &op2) {
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
    
    return source;
}

std::ostream &operator<<(std::ostream &op1, const BMP_Header &op2) {
    op1 << "BMP Header: "          << std::endl
        << "Header ID: "           << op2.field[0] << op2.field[1] << std::endl
        << "Size of file: "        << op2.size_of  << std::endl
        << "Reserved: "            << op2.reserved << std::endl
        << "Pixel Grid offset: 0x" << std::hex     << op2.offset ;
    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const BMP_Header &op2) {
    op1.write(&op2.field[0], 1);
    op1.write(&op2.field[1], 1);
    op1.write(reinterpret_cast<const char *> (&op2.size_of),  4);
    op1.write(reinterpret_cast<const char *> (&op2.reserved), 4);
    op1.write(reinterpret_cast<const char *> (&op2.offset),   4);
    return op1;
}

std::ifstream & operator>>(std::ifstream &source, DIB_Header &op2) {
    try 
    {
        source >> op2.header_size;
        const int header_id = op2.header_size;

        // Support for BITMAPCOREHEADER, which has a different format
        if (header_id == 12){
            uint16_t n = 0;
            source >> n; op2.width += n;
            source >> n; op2.height += n;
            source >> op2.color_planes;
            source >> op2.depth;
            return source;
        }
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
    }

    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return source;
}

std::ostream &operator<<(std::ostream &op1, const DIB_Header &op2) {
    op1 << "DIB Header:"            << std::endl
        << "Header Size: "          << std::dec             << op2.header_size  << std::endl
        << "Image w x h: "          << op2.width            << " x "            << op2.height << std::endl
        << "Color Planes: "         << op2.color_planes     << std::endl
        << "Bit depth: "            << op2.depth            << std::endl
        << "Compression: "          << op2.compression_type << std::endl
        << "sizeOf img data: 0x"    << std::hex             << op2.img_size     << std::endl
        << "Resolution, px/m: 0x"   << std::hex             << op2.h_resolution << "h x 0x" << std::hex << op2.v_resolution << "w"<< std::endl
        << "Colors: " << op2.colors << std::endl
        << "Important colors: 0x"   << std::hex             << op2.important;
    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const DIB_Header &op2) {
    op1.write(reinterpret_cast<const char *>(&op2.header_size),         sizeof(op2.header_size));
    op1.write(reinterpret_cast<const char *>(&op2.width),               sizeof(op2.width));
    op1.write(reinterpret_cast<const char *>(&op2.height),              sizeof(op2.height));
    op1.write(reinterpret_cast<const char *>(&op2.color_planes),        sizeof(op2.color_planes));
    op1.write(reinterpret_cast<const char *>(&op2.depth),               sizeof(op2.depth));
    op1.write(reinterpret_cast<const char *>(&op2.compression_type),    sizeof(op2.compression_type));
    op1.write(reinterpret_cast<const char *>(&op2.img_size),            sizeof(op2.img_size));
    op1.write(reinterpret_cast<const char *>(&op2.h_resolution),        sizeof(op2.h_resolution));
    op1.write(reinterpret_cast<const char *>(&op2.v_resolution),        sizeof(op2.v_resolution));
    op1.write(reinterpret_cast<const char *>(&op2.colors),              sizeof(op2.colors));
    op1.write(reinterpret_cast<const char *>(&op2.important),           sizeof(op2.important));

    return op1;
}

std::ifstream &operator>>(std::ifstream &op1, uint16_t &op2) {
    op1.read(reinterpret_cast<char*>(&op2), 2);
    return op1;
}

std::ifstream &operator >>(std::ifstream &op1, RGB_24_c &op2) {
    op2.color[0] = op1.get();
    op2.color[1] = op1.get();
    op2.color[2] = op1.get();

    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const RGB_24_c &op2) {
    const char * head = reinterpret_cast<const char*> (&op2.color);
    op1.write(head, 3);

    return op1;
}

std::ifstream &operator>>(std::ifstream &op1, BitMap &op2) {
    op1 >> op2.bmpHeader;
    op1 >> op2.dibHeader;

    assert(!std::strcmp(op2.bmpHeader.field, BMP::BMP_FIELD));

    op1.seekg(op2.bmpHeader.offset);
    op2.load_imgData(op1);

    return op1;
}

std::ofstream &operator<<(std::ofstream &op1, const BitMap &op2) {
    op1 << op2.bmpHeader
        << op2.dibHeader;

    uint32_t cols = op2.imgData[0].size();

    for(uint32_t r = 0; r < op2.imgData.size(); r++){
        for(uint32_t c = 0; c < cols; c++){
            op1 << op2.imgData[r][c];
        }
    }

    return op1;
}

std::ifstream &operator>>(std::ifstream &op1, uint32_t &op2) {
    op1.read(reinterpret_cast<char*>(&op2), 4);
    return op1;
}

std::ifstream &operator>>(std::ifstream &op1, int32_t &op2) {
    op1.read(reinterpret_cast<char*>(&op2), 4);
    return op1;
}

BitMap::BitMap() : bmpHeader({0}), dibHeader({0}), padding(0), imgData({0})
{}

BitMap::BitMap(const std::string &path) : bmpHeader(), dibHeader(), padding(0), imgData({0}), palette() {
    std::ifstream iFile;

    iFile.open(path);

    iFile >> *this;

    iFile.close();
}

void PixelArray::extract(const BitMap & source) {
    width = source.dibHeader.width;
    height = source.dibHeader.height;

    data = std::vector<std::vector<Color>>(width, std::vector<Color>(height, Color {0}));

    int colorType = source.dibHeader.depth;
    int padding = source.padding;

}


std::ifstream & BitMap::load_imgData(std::ifstream & source) {

    uint32_t width = std::ceil((dibHeader.width * dibHeader.depth)/8.0);
    padding = width % 4;

    const uint32_t rows = dibHeader.height;
    const uint32_t cols = width + padding;

    imgData = std::vector<std::vector<char>>(rows, std::vector<char>(cols, char{0}));
    
    for (uint32_t r = 0; r < rows; r++) {
        for (uint32_t c = 0; c < cols; c++) {
            source >> imgData[r][c];
        }
    }
    return source;

}

PixelArray::PixelArray(int h, int w) : height(h), width(w), data()
{}
