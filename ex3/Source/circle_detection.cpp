#include "circle_detection.h"

// 进行圆检测
void detectCircles(const cv::Mat& inputImage, std::vector<cv::Vec3f>& circles) {
    // 图像预处理，例如灰度化、边缘检测等
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

    // 使用Canny进行边缘检测
    cv::Mat edges;
    cv::Canny(grayImage, edges, 50, 150);

    // 寻找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 过滤掉小轮廓
    contours.erase(std::remove_if(contours.begin(), contours.end(),
        [](const std::vector<cv::Point>& contour) {
            return cv::contourArea(contour) < 100; // 可以根据图像和需求调整阈值
        }), contours.end());

    // 拟合椭圆
    for (const auto& contour : contours) {
        cv::RotatedRect ellipse = cv::fitEllipse(contour);
        circles.push_back({ ellipse.center.x, ellipse.center.y, (ellipse.size.width + ellipse.size.height) / 4.0f });
    }
}

// 在图像上绘制检测到的圆
// cvRound() 取整数
// circle[0] 是圆心的 x 坐标。
// circle[1] 是圆心的 y 坐标。
// circle[2] 是圆的半径。
void drawCircles(cv::Mat& image, const std::vector<cv::Vec3f>& circles) {
    // 在图像上绘制检测到的圆
    for (const auto& circle : circles) {
        cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
        int radius = cvRound(circle[2]);
        // 使用红色标记圆
        cv::circle(image, center, radius, cv::Scalar(0, 0, 255), 2);
    }
}

int main_detectCircles(){

    // 读取图像
    cv::Mat image_circle = cv::imread(img_circle_inputfilename);

    if(image_circle.empty()){
        std::cerr << "detectCircles Failed! because inputImage is empty!\n";
        return 0;
    }

    // 进行圆检测
    std::vector<cv::Vec3f> circles;
    detectCircles(image_circle, circles);

    // 在图像上绘制检测到的圆
    drawCircles(image_circle, circles);

    // 显示结果
    cv::imshow("Detected Circles", image_circle);

    // 保存处理后的图像为 BMP 格式
    cv::imwrite(img_circle_outputfilename, image_circle);

    return 1;
}
