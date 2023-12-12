// BMP.h
#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

// Constants 
const char BMP_FIELD[2] =  { '\x42', '\x4d'} ;
const uint16_t RESERVED = 0x0000;

const uint16_t DIB_SIZE = 40;
const uint8_t COLOR_PLANE = 0x01;
const uint16_t DIB_IMPORTANT = 0;

const uint32_t MASK = 255;

// Structs

// Header
// field, size_of, reserved, offset;
struct BMP_Header 
{

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
struct DIB_Header 
{
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
    uint32_t important;

};


// ?Extra bit Masks

struct RGBA_32_c
{
    uint32_t color;
};

struct RGBA_16_c
{
    uint16_t color;
};

// 0x00RRGGBB
struct RGB_24_c
{
    uint32_t color;
};

template <typename TYPE>
struct palette
{
    std::vector<TYPE> colors;
};

// Gap1 

/// @brief Array of pixel values
/// @tparam TYPE 
template <typename TYPE>
struct PixelArray
{
    PixelArray(int h, int w);

    typedef std::vector<TYPE> rowVector;

    std::vector<rowVector> data;
    int rows;
    int cols;
};

// Gap2

// ?ICC color profile

// Declarations

/// @brief Given a .bmp, extract header into header struct
BMP_Header & operator>> (std::ifstream & op1, BMP_Header & op2);

std::ostream & operator<<(std::ostream & op1, const BMP_Header & op2);
std::ofstream & operator<<(std::ofstream & op1, const BMP_Header & op2);

/// @brief Given a .bmp, extract DIB header info into DIB header struct
DIB_Header & operator>> (std::ifstream & op1, DIB_Header & op2);

std::ostream & operator<<(std::ostream & op1, const DIB_Header & op2);
std::ofstream & operator<<(std::ofstream & op1, const DIB_Header & op2);

/// @brief Extracts the next 4 chars into a uint32
uint32_t extract_uint32(std::ifstream & source);

/// @brief Extracts the next 4 chars into a signed int32
int32_t extract_int32(std::ifstream &source);

/// @brief Extracts the next 2 chars int0 a uint 16
uint16_t extract_uint16(std::ifstream &source);

/// @brief Extracts the next 3 chars into a 24 bit color
std::ifstream & operator>> (std::ifstream & op1, RGB_24_c & op2);

std::ofstream & operator<<(std::ofstream & op1, const RGB_24_c &op2);

template <typename TYPE>
std::ofstream & operator<<(std::ofstream & op1, const PixelArray<TYPE> & op2);

template <typename TYPE>
std::ifstream & operator>>(std::ifstream & op1,  PixelArray<TYPE> & op2);


#include "BMP.tpp"

