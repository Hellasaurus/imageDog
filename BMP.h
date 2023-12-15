// BMP.h
#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <ostream>
#include <fstream>
#include <assert.h>

// Constants 
namespace BMP {

    const char BMP_FIELD[2] =  { '\x42', '\x4d'} ;
    const uint16_t RESERVED = 0x0000;

    const uint16_t DIB_SIZE = 40;
    const uint8_t COLOR_PLANE = 0x01;
    const uint16_t DIB_IMPORTANT = 0;

    const uint32_t MASK = 255;
}

// Structs

// Header
// field, size_of, reserved, offset;
struct BMP_Header {

    // header field, should be BM, i.e. 0x42, 0x4d, 2b
    char field[2];
    // Size of BMP in Bytes, 4b 
    uint32_t size_of;
    // Reserved, not currently used in this implementation, 4b
    uint32_t reserved;
    // Offset of the byte where pixel array can be found, 4b
    uint32_t offset;
};

// DIB Header
struct DIB_Header {

    // using Windows BITMAPINFOHEADER STANDARD
    uint32_t header_size;
    uint32_t width;
    uint32_t height;
    // number of color planes (must be 1)
    uint16_t color_planes;
    // number of bits per pixel, typically 1, 4, 8, 16, 32
    uint16_t depth;
    // compression method being used, usually 0
    uint32_t compression_type;
    // image size, or size of raw bmp data
    uint32_t img_size;
    // resolution, in px/m
    int32_t h_resolution;
    int32_t v_resolution;
    // number of colors in the palette
    uint32_t colors;
    // number of important colors
    uint32_t important;

};


// ?Extra bit Mask

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

// r, g, b
struct RGB_24_c {
    unsigned char color[3];
    //uint32_t color;
};


struct BitMap {
    BitMap();
    BitMap(const std::string & path);

    BMP_Header bmpHeader;
    DIB_Header dibHeader;

    uint16_t padding;

    std::vector<Color> palette;

    std::ifstream & load_imgData(std::ifstream & source);
    std::vector<std::vector<char>> imgData;
    
};

/// @brief Array of pixel values
struct PixelArray {
    PixelArray(int height, int width);

    void extract(const BitMap & source);

    std::vector<std::vector<Color>> data;
    int width;
    int height;
};


// Gap2

// ?ICC color profile

// Declarations

// BMP Header i/o
std::ostream  & operator<<(std::ostream  & op1, const BMP_Header & op2);
std::ifstream & operator>>(std::ifstream & op1, BMP_Header & op2);
std::ofstream & operator<<(std::ofstream & op1, const BMP_Header & op2);

// DIB Header i/o
std::ostream  & operator<<(std::ostream  & op1, const DIB_Header & op2);
std::ifstream & operator>>(std::ifstream & op1, DIB_Header & op2);
std::ofstream & operator<<(std::ofstream & op1, const DIB_Header & op2);

// Bitmap i/o
std::ifstream & operator>>(std::ifstream & op1, const BitMap & op2);
std::ofstream & operator<<(std::ofstream & op1, const BitMap & op2);

std::ifstream & operator>>(std::ifstream & op1, uint16_t & op2);
std::ifstream & operator>>(std::ifstream & op1, uint32_t & op2);
std::ifstream & operator>>(std::ifstream & op1, int32_t  & op2);

std::ifstream & operator>>(std::ifstream & op1, RGB_24_c & op2);
std::ofstream & operator<<(std::ofstream & op1, const RGB_24_c &op2);



