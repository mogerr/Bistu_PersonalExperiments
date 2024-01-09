#include <opencv2/opencv.hpp>
#include "display.h"

void displayImage(const std::string& fileName) {
    // Read the processed image using OpenCV
    cv::Mat image = cv::imread(fileName, cv::IMREAD_UNCHANGED);

    if (image.empty()) {
        std::cerr << "Failed to open image for display.\n";
        return;
    }
    else{
        std::cerr << "The image is not empty.\n";
    }
    

    // Display the image
    cv::imshow("Processed Image", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}


void displayImage(const std::vector<std::string>& fileNames) {
    // Check if two file names are provided
    if (fileNames.size() != 2) {
        std::cerr << "Error: Two file names are required.\n";
        return;
    }

    // Read the input and processed images using OpenCV
    std::vector<cv::Mat> images;
    for (const auto& fileName : fileNames) {
        cv::Mat image = cv::imread(fileName, cv::IMREAD_UNCHANGED);
        if (image.empty()) {
            std::cerr << "Failed to open image: " << fileName << "\n";
            return;
        }
        images.push_back(image);
    }

    // Create a window to display the images side by side
    cv::namedWindow("Input and Processed Images", cv::WINDOW_NORMAL);

    // Calculate the width and height of the window
    int totalWidth = images[0].cols + images[1].cols;
    int maxHeight = std::max(images[0].rows, images[1].rows);

    // Resize the window to fit both images
    cv::resizeWindow("Input and Processed Images", totalWidth, maxHeight);

    // Create a blank canvas to display the images
    cv::Mat canvas = cv::Mat::zeros(maxHeight, totalWidth, images[0].type());

    // Copy the input image to the left side of the canvas
    images[0].copyTo(canvas(cv::Rect(0, 0, images[0].cols, images[0].rows)));

    // Copy the processed image to the right side of the canvas
    images[1].copyTo(canvas(cv::Rect(images[0].cols, 0, images[1].cols, images[1].rows)));

    // Display the canvas
    cv::imshow("Input and Processed Images", canvas);
    cv::waitKey(0);
    cv::destroyAllWindows();
}