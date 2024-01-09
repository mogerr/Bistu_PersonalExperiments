// #include "stdafx.h"
#include "circular.h"

using namespace std;


// 构造函数的三种重载
CCircle::CCircle() : CPoint(), radius(0.0) 
{

}

CCircle::CCircle(double x, double y, double r) : CPoint(x, y), radius(r)
{

}

CCircle::CCircle(const CPoint& p, double r) : CPoint(p), radius(r)
{

}

// 析构函数
CCircle::~CCircle() {
    //std::cout << "Circle destructor called." << std::endl;
}

void CCircle::Show() const {
    // 调用基类的 Show 函数
    std::cout << "圆心 of Circle: "; CPoint::Show(true, true); std::cout << std::endl;
    std::cout << "半径 of Circle: " << radius << std::endl;
    std::cout << "面积 of Circle: " << CCircle::GetArea() << std::endl;
    std::cout << "周长 of circle: " << CCircle::GetPerimeter() << std::endl;
}

// 获取圆的面积
double CCircle::GetArea() const {
    return 3.14159 * radius * radius;
}

// 获取半径
double CCircle::GetRadius() const {
    return radius;
}

// 获取圆心坐标
double CCircle::GetCenterX() const {
    return GetX();}
double CCircle::GetCenterY() const {
    return GetY();}


// 获取圆的周长
double CCircle::GetPerimeter() const {
    return 2.0 * 3.14159 * radius;
}






void testCCircle() {

    std::cout << endl << "这是 testCCircle() 函数" << endl;

    // 创建CCircle对象，并调用两种构造函数
    CPoint  point;
    CCircle circle1(point,4);
    CCircle circle2(3.0, 4.0, 2.5);

    // 调用虚函数 Show 来输出几何特征
    circle1.Show();

    // 获取圆的半径、圆心坐标和周长并打印
    std::cout << std::endl;
    std::cout << "圆心 of circle_2: (" << circle2.GetCenterX() << ", " << circle2.GetCenterY() << ")" << std::endl;
    std::cout << "半径 of circle_2: " << circle2.GetRadius() << std::endl;
    std::cout << "周长 of circle_2: " << circle2.GetPerimeter() << std::endl;
    std::cout << std::endl;
}