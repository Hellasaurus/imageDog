// BMPread.h
#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

#include "BMPencode.h"

/// @brief Given a .bmp, extract header into header struct
struct BMP_Header get_BMP_header(std::fstream & source);

/// @brief Given a .bmp, extract DIB header info into DIB header struct
struct DIB_Header get_DIB_header(std::fstream & source);

/// @brief Given 4 chars, concatenate into one uint16
/// @param a 
/// @param b 
/// @param c 
/// @param d 
/// @return 0xaabbccdd
uint16_t char_to_uint16(char a, char b, char c, char d);
