#pragma once
#ifndef LINE_DETECTION_H
#define LINE_DETECTION_H

#include <opencv2/opencv.hpp>
#include <vector>

#define  img_line_inputfilename    "img1_line.bmp"
#define  img_line_outputfilename   "img1_line_out.bmp"

// º¯ÊýÉùÃ÷
void detectLines(const cv::Mat& inputImage, std::vector<cv::Vec4i>& lines);
void drawLines(cv::Mat& image, const std::vector<cv::Vec4i>& lines);
int main_detectLines();

#endif // LINE_DETECTION_H
