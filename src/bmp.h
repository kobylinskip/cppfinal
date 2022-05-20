/*
    Name: Phillip Kobylinski
    File: bmp.h
    Date: 05/11/2022
    Assignment: Final Project
    Description: Header for .bmp file output code
    License: See LICENSE.txt
*/

#ifndef BMP_H_INCLUDED
#define BMP_H_INCLUDED

#include <cstdint>
#include <fstream>

void WriteBMP(std::ofstream &file, uint32_t *pixels, int width, int height);

#endif // BMP_H_INCLUDED
