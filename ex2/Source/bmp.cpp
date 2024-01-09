#include "bmp.h"

bool processImage(const std::string& inputFileName, const std::string& outputFileName) {
    // 读取 BMP 文件
    std::ifstream inputFile(inputFileName, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file.\n";
        return false;
    }

    // 读取 BMP 文件头
    BMPHeader bmpHeader;
    inputFile.read(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));

    // 读取 BMP 信息头
    BMPInfoHeader bmpInfoHeader;
    inputFile.read(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    // 检查是否为24位 BMP 图像
    if (bmpInfoHeader.bitCount != 24) {
        std::cerr << "Only 24-bit BMP images are supported.\n";
        return false;
    }

    // 计算图像行字节数，并准备容器存储像素数据
    int rowSize = (bmpInfoHeader.width * 3 + 3) & ~3; // 每行的字节数需要为4的倍数
    std::vector<uint8_t> imageData(rowSize * bmpInfoHeader.height);

    // 读取像素数据
    inputFile.read(reinterpret_cast<char*>(imageData.data()), imageData.size());
    inputFile.close();

    // 转换为灰度图
    for (int i = 0; i < imageData.size(); i += 3) {
        // 使用简单的灰度公式：Gray = 0.299*R + 0.587*G + 0.114*B
        uint8_t gray = static_cast<uint8_t>(0.299 * imageData[i] + 0.587 * imageData[i + 1] + 0.114 * imageData[i + 2]);
        imageData[i] = imageData[i + 1] = imageData[i + 2] = gray;
    }

    // 写入 BMP 文件
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file.\n";
        return false;
    }

    // 写入 BMP 文件头和信息头
    outputFile.write(reinterpret_cast<char*>(&bmpHeader), sizeof(BMPHeader));
    outputFile.write(reinterpret_cast<char*>(&bmpInfoHeader), sizeof(BMPInfoHeader));

    // 写入转换后的像素数据
    outputFile.write(reinterpret_cast<char*>(imageData.data()), imageData.size());
    outputFile.close();

    return true;
}