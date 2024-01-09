#include "line_detection.h"

void detectLines(const cv::Mat& inputImage, std::vector<cv::Vec4i>& lines) {
    // ͼ��Ԥ��������ҶȻ�����Ե����
    cv::Mat grayImage;
    cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

    cv::Mat edges;
    cv::Canny(grayImage, edges, 50, 150);

    // ����ֱ�߼��
    cv::HoughLinesP(edges, lines, 1, CV_PI / 180, 50, 50, 10);
}

void drawLines(cv::Mat& image, const std::vector<cv::Vec4i>& lines) {
    // ��ͼ���ϻ���ֱ��
    for (const auto& line : lines) {
        cv::line(image, cv::Point(line[0], line[1]), cv::Point(line[2], line[3]), cv::Scalar(0, 0, 255), 2);
    }
}

int main_detectLines(){

    // ��ȡͼ��
    cv::Mat image_line = cv::imread(img_line_inputfilename);

    if(image_line.empty()){
        std::cerr << "detectLines Failed! because inputImage is empty!\n";
        return 0;
    }

    // ����ֱ�߼��
    std::vector<cv::Vec4i> lines;
    detectLines(image_line, lines);

    // ��ͼ���ϻ��Ƽ�⵽��ֱ��
    drawLines(image_line, lines);

    // ��ʾ���
    cv::imshow("Detected Lines", image_line);

    // ���洦����ͼ��Ϊ BMP ��ʽ
    cv::imwrite(img_line_outputfilename, image_line);
    
    return 1;
}