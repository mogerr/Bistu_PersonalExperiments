#pragma once
#include <cstdint> // 包含这个头文件以获取uint16_t等类型定义
#include <vector>
#include <iostream>
#include <fstream>

//对齐 开始
#pragma pack(push, 1)

// BMP文件头结构
struct BMPHeader {
    char signature[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

// BMP信息头结构
struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};

//对齐 结束
#pragma pack(pop)

bool processImage(const std::string& inputFileName, const std::string& outputFileName);





