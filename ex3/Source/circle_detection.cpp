#include "circle_detection.h"

// ����Բ���
void detectCircles(const cv::Mat& inputImage, std::vector<cv::Vec3f>& circles) {
    // ͼ��Ԥ��������ҶȻ�����Ե����
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

    // ʹ��Canny���б�Ե���
    cv::Mat edges;
    cv::Canny(grayImage, edges, 50, 150);

    // Ѱ������
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // ���˵�С����
    contours.erase(std::remove_if(contours.begin(), contours.end(),
        [](const std::vector<cv::Point>& contour) {
            return cv::contourArea(contour) < 100; // ���Ը���ͼ������������ֵ
        }), contours.end());

    // �����Բ
    for (const auto& contour : contours) {
        cv::RotatedRect ellipse = cv::fitEllipse(contour);
        circles.push_back({ ellipse.center.x, ellipse.center.y, (ellipse.size.width + ellipse.size.height) / 4.0f });
    }
}

// ��ͼ���ϻ��Ƽ�⵽��Բ
// cvRound() ȡ����
// circle[0] ��Բ�ĵ� x ���ꡣ
// circle[1] ��Բ�ĵ� y ���ꡣ
// circle[2] ��Բ�İ뾶��
void drawCircles(cv::Mat& image, const std::vector<cv::Vec3f>& circles) {
    // ��ͼ���ϻ��Ƽ�⵽��Բ
    for (const auto& circle : circles) {
        cv::Point center(cvRound(circle[0]), cvRound(circle[1]));
        int radius = cvRound(circle[2]);
        // ʹ�ú�ɫ���Բ
        cv::circle(image, center, radius, cv::Scalar(0, 0, 255), 2);
    }
}

int main_detectCircles(){

    // ��ȡͼ��
    cv::Mat image_circle = cv::imread(img_circle_inputfilename);

    if(image_circle.empty()){
        std::cerr << "detectCircles Failed! because inputImage is empty!\n";
        return 0;
    }

    // ����Բ���
    std::vector<cv::Vec3f> circles;
    detectCircles(image_circle, circles);

    // ��ͼ���ϻ��Ƽ�⵽��Բ
    drawCircles(image_circle, circles);

    // ��ʾ���
    cv::imshow("Detected Circles", image_circle);

    // ���洦����ͼ��Ϊ BMP ��ʽ
    cv::imwrite(img_circle_outputfilename, image_circle);

    return 1;
}
