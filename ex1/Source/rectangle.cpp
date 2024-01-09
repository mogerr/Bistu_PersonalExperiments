// #include "stdafx.h"
#include "rectangle.h"
#include "math.h"

using namespace std;

// 构造函数的两种重载
CRectangle::CRectangle() : CPoint(), width(0.0), height(0.0) 
{

}

CRectangle::CRectangle(const CPoint& t) : CPoint(t), width(0.0), height(0.0) 
{

}

CRectangle::CRectangle(double x, double y, double w, double h)
	: CPoint(x, y), width(w), height(h) 
{

}

// 析构函数
CRectangle::~CRectangle() {
	//std::cout << "Rectangle destructor called." << std::endl;
}


// 重写基类虚函数
void CRectangle::Show() const {
	// 调用基类的 Show 函数
	std::cout << "矩形左上角的坐标: ";  CPoint::Show(true, true);  std::cout << std::endl;
	std::cout << "矩形的 width : " << width << ", height: " << height << std::endl;
}

// 获取矩形的面积
double CRectangle::GetArea() const {
	return width * height;
}

// 获取矩形的周长
double CRectangle::GetPerimeter() const {
	return 2.0 * (width + height);
}



void testCRectangle()
{
	std::cout << endl << "这是 testCRectangle() 函数" << endl;

	// 创建CRectangle对象，并调用两种构造函数
	CRectangle rectangle1;
	CRectangle rectangle2(1.0, 2.0, 3.0, 4.0);

	// 调用虚函数 Show 来输出几何特征
	rectangle1.Show();
	std::cout << std::endl;
	rectangle2.Show();

	// 获取矩形的面积、周长并打印
	std::cout << "矩形的面积: " << rectangle2.GetArea() << std::endl;
	std::cout << "矩形的周长: " << rectangle2.GetPerimeter() << std::endl << std::endl;
}