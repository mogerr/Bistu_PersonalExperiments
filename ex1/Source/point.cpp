
#include "point.h"

using namespace std;

CPoint::CPoint()
{
	x_p = 0.0;  y_p = 0.0;
};

CPoint::CPoint(double x = 0.0, double y = 0.0) : x_p(x), y_p(y)
{

};

CPoint::CPoint(const CPoint& old)
{
	x_p = old.x_p;
	y_p = old.y_p;
};

CPoint::~CPoint()
{
	// cout<<"\n Point has been ~????~ \n";
}

double CPoint::GetX() const
{
	return x_p;
}

double CPoint::GetY() const
{
	return y_p;
}


// 重载 - 运算符
CPoint CPoint::operator-(const CPoint& other) const {
	return CPoint(   x_p - other.x_p,    y_p - other.y_p   );
}

// 重载 + 运算符
CPoint CPoint::operator+(const CPoint& other) const {
	return CPoint(	x_p + other.x_p,	 y_p + other.y_p);
}

// 以cout的方式输出（带提示）
void CPoint::Show() const
{
	cout << "该点的二维笛卡尔坐标为: ";
	cout << "(" << x_p << "," << y_p << ")" << endl;
}

// 以cout的方式输出（不带提示）
void CPoint::Show(bool x, bool  y)const {
	cout << "(" << x_p << "," << y_p << ")";
}

// 以字符串的方式输出
std::string CPoint::Show(std::string preStr) const  {
	return preStr + "(" + std::to_string(x_p) + "," + std::to_string(y_p) + ")";
}




/**
 * @brief  重载运算符 -  + 测试函数
 * @return 
 */
void test_CPoint() {

	cout << endl << "这是 test_CPoint() 函数：" << endl;

    CPoint point1(3.0, 4.0);
    CPoint point2(1.0, 2.0);

	// 打印结果
	point1.Show();
	point2.Show();

    // 使用 - 运算符
    CPoint result1 = point1 - point2;

    // 打印结果
    //result1.Show();
	cout << result1.Show("") << "=" << point1.Show("") << "-" << point2.Show("") << endl;

	// 使用 + 运算符
    CPoint result2 = point1 + point2;

    // 打印结果
    result2.Show();
	cout << result2.Show("") << "=" << point1.Show("") << "+" << point2.Show("") << endl <<endl;
}