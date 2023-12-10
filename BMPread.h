// BMPread.h
#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>

#include "BMPencode.h"

/// @brief Given a .bmp, extract header into header struct
struct BMP_Header get_BMP_header(std::ifstream & source);

std::ostream & operator<<(std::ostream & op1, const BMP_Header & op2);

/// @brief Given a .bmp, extract DIB header info into DIB header struct
struct DIB_Header get_DIB_header(std::ifstream & source);

std::ostream & operator<<(std::ostream & op1, const DIB_Header & op2);

/// @brief Extracts the next 4 chars into a uint32
uint32_t extract_uint32(std::ifstream & source);

/// @brief Extracts the next 4 chars into a signed int32
int32_t extract_int32(std::ifstream &source);

/// @brief Extracts the next 2 chars int a uint 16
uint16_t extract_uint16(std::ifstream &source);

