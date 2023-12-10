// BMPencode.h
#pragma once

#include <iostream>
#include <cstdint>
#include <vector>


const char BMP_FIELD[2] =  { '\x42', '\x4d'} ;
const uint16_t RESERVED = 0x0000;

const uint16_t DIB_SIZE = 40;
const uint8_t COLOR_PLANE = 0x01;
const uint16_t DIB_IMPORTANT = 0;

// Header
// field, size_of, reserved, offset;
struct BMP_Header 
{

    // header field, should be BM, i.e. 0x42, 0x4d, 2b
    char field[2];

    // Size of BMP in Bytes, 4b 
    uint16_t size_of;

    // Reserved, not currently used in this implementation, 4b
    uint16_t reserved;

    // Offset of the byte where pixel array can be found, 4b
    uint16_t offset;
};

// DIB Header
struct DIB_Header 
{
    // using Windows BITMAPINFOHEADER STANDARD

    uint16_t header_size;

    uint16_t width;
    uint16_t height;

    // number of color planes (must be 1)
    uint8_t color_planes;

    // number of bits per pixel, typically 1, 4, 8, 16, 32
    uint8_t depth;

    // compression method being used, usually 0
    uint16_t compression_type;

    // image size, or size of raw bmp data
    uint16_t img_size;

    // resolution, in px/m
    int8_t h_resolution;
    int8_t v_resolution;

    // number of colors in the palette
    uint16_t colors;
    uint16_t important;

};


// ?Extra bit Masks

struct RGBA_32_c
{
    uint32_t color;
};

struct palette
{
    std::vector<RGBA_32_c> colors;
};

struct Color1
{
    bool value;
};

struct Color2
{
    char * pixel[4];
};

struct Color4
{
    char * pixel[2];
};

struct Color8
{
    char value;
};

struct Color16
{
    char ARChannel;
    char GBChannel;
};

struct Color24
{
    uint32_t value;
};

struct Color32
{
    uint32_t value;
};

// Gap1 

// PixelArray

// Gap2

// ?ICC color profile