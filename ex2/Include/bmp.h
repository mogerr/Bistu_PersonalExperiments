#pragma once
#include <cstdint> // �������ͷ�ļ��Ի�ȡuint16_t�����Ͷ���
#include <vector>
#include <iostream>
#include <fstream>

//���� ��ʼ
#pragma pack(push, 1)

// BMP�ļ�ͷ�ṹ
struct BMPHeader {
    char signature[2];
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
};

// BMP��Ϣͷ�ṹ
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

//���� ����
#pragma pack(pop)

bool processImage(const std::string& inputFileName, const std::string& outputFileName);





