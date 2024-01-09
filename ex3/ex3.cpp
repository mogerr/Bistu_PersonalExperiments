// ex3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "line_detection.h"
#include "circle_detection.h"


int main() {


     if (main_detectLines())
     {
         //等待按键事件
         //cv::waitKey(0);
     }
    if (main_detectCircles())
    {
        // 等待按键事件
        // cv::waitKey(0);
    }
        
    

    // // 读取图像
    // cv::Mat image_line = cv::imread(img_line_inputfilename);

    // if(image_line.empty()){
    //     std::cerr << "detectLines Failed! because inputImage is empty!\n";
    //     return 0;
    // }

    // // 进行直线检测
    // std::vector<cv::Vec4i> lines;
    // detectLines(image_line, lines);

    // // 在图像上绘制检测到的直线
    // drawLines(image_line, lines);

    // // 显示结果
    // cv::imshow("Detected Lines", image_line);

    // // 保存处理后的图像为 BMP 格式
    // cv::imwrite(img_line_outputfilename, image_line);

    // 等待按键事件
    cv::waitKey(0);

    system("pause");
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
