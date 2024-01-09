
#include "line.h"

using namespace std;

CLine::CLine() : CPoint(), length(0.0), endX(0.0), endY(0.0) 
{

}

CLine:: CLine(double x1, double y1, double x2, double y2)
    : CPoint(x1, y1), endX(x2), endY(y2) {
    CalculateLength();
}

// 析构函数
CLine::~CLine() {
    //std::cout << "Line destructor called." << std::endl;
}

// 重写基类虚函数
void CLine::Show() const {
    std::cout << "这是一条线  ";
    // 调用基类的 Show 函数
    std::cout << CPoint::Show("起点: ") ; 
    std::cout << "  终点: (" << CLine::endX  << "," << CLine::endY << ")" << std::endl;
    std::cout << "Line length: " <<  CLine::getlength()  << std::endl;
}

// 计算线段长度
void CLine::CalculateLength() {
    CLine::length = std::sqrt(std::pow(endX - x_p, 2) + std::pow(endY - y_p, 2));
}

// 获取长度
double CLine::getlength() const {
    return CLine::length;
}


void testCLine() {

    std::cout << endl << "这是 testCLine() 函数" << endl;

    // 创建CLine对象，并调用两种构造函数
    CLine line1;
    CLine line2(1.0, 2.0, 4.0, 6.0);

    // 调用虚函数 Show 来输出几何特征
    line1.Show();
    line2.Show();

    std::cout << endl;
}