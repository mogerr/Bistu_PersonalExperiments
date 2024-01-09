#pragma once
#ifndef CIRCLE_DETECTION_H
#define CIRCLE_DETECTION_H

#include <opencv2/opencv.hpp>
#include <vector>

#define  img_circle_inputfilename    "img2_circle.bmp"
#define  img_circle_outputfilename   "img2_circle_out.bmp"

// º¯ÊýÉùÃ÷
void detectCircles(const cv::Mat& inputImage, std::vector<cv::Vec3f>& circles);
void drawCircles(cv::Mat& image, const std::vector<cv::Vec3f>& circles);
int main_detectCircles();

#endif // CIRCLE_DETECTION_H