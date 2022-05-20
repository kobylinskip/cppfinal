/*
    Name: Phillip Kobylinski
    File: bmp.cpp
    Date: 05/11/2022
    Assignment: Final Project
    Description: Code for outputting .bmp files
    License: See LICENSE.txt
*/

#include "bmp.h"

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t fileType;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t bitmapOffset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader
{
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPx;
    uint32_t compression;
    uint32_t sizeOfBitmap;
    int32_t horzResolution;
    int32_t vertResolution;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPColorHeader
{
    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;
    uint32_t colorSpace;
    uint32_t unused[16];
};
#pragma pack(pop)

//
// Function:    WriteBMP
// Parameters:  Output file, pixel array, width, height
// Returns:     None
// Description: Output pixel image to a .bmp file
//
void WriteBMP(std::ofstream &file, uint32_t *pixels, int width, int height)
{
    size_t headerSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
    size_t bitmapSize = sizeof(*pixels) * width * height;
    size_t fileSize = headerSize + bitmapSize;

    BMPFileHeader fileHeader = {};
    fileHeader.fileType = 0x4D42; // The signature for a BMP file
    fileHeader.fileSize = uint32_t(fileSize);
    fileHeader.bitmapOffset = uint32_t(headerSize);

    BMPInfoHeader infoHeader = {};
    infoHeader.size = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = -height;
    infoHeader.planes = 1;
    infoHeader.bitsPerPx = 32;
    infoHeader.compression = 3; // Disable compression
    infoHeader.sizeOfBitmap = uint32_t(bitmapSize);
    infoHeader.horzResolution = width;
    infoHeader.vertResolution = height;

    BMPColorHeader colorHeader = {};
    colorHeader.redMask = 0xFF000000;
    colorHeader.greenMask = 0x00FF0000;
    colorHeader.blueMask = 0x0000FF00;
    colorHeader.alphaMask = 0x000000FF;
    colorHeader.colorSpace = 0x73524742; // sRGB

    file.write((const char *)&fileHeader, sizeof(fileHeader));
    file.write((const char *)&infoHeader, sizeof(infoHeader));
    file.write((const char *)&colorHeader, sizeof(colorHeader));
    file.write((const char *)pixels, bitmapSize);
}
