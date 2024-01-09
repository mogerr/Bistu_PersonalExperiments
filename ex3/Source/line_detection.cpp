#include "line_detection.h"

void detectLines(const cv::Mat& inputImage, std::vector<cv::Vec4i>& lines) {
    // 图像预处理，例如灰度化、边缘检测等
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

    cv::Mat edges;
    cv::Canny(grayImage, edges, 50, 150);

    // 进行直线检测
    cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);
}

void drawLines(cv::Mat& image, const std::vector<cv::Vec4i>& lines) {
    // 在图像上绘制直线
    for (const auto& line : lines) {
        cv::line(image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 2);
    }
}

int main_detectLines(){

    // 读取图像
    cv::Mat image_line = cv::imread(img_line_inputfilename);

    if(image_line.empty()){
        std::cerr << "detectLines Failed! because inputImage is empty!\n";
        return 0;
    }

    // 进行直线检测
    std::vector<cv::Vec4i> lines;
    detectLines(image_line, lines);

    // 在图像上绘制检测到的直线
    drawLines(image_line, lines);

    // 显示结果
    cv::imshow("Detected Lines", image_line);

    // 保存处理后的图像为 BMP 格式
    cv::imwrite(img_line_outputfilename, image_line);
    
    return 1;
}