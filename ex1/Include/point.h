#pragma once
#include <string>
#include <iostream>



class CPoint
{
public:
	// 构造 （三种重载）
	CPoint();

	CPoint(double , double );

	CPoint(const CPoint& );

	~CPoint();

	// 重载 - 运算符
	CPoint operator-(const CPoint& ) const;

	// 重载 + 运算符
	CPoint operator+(const CPoint& ) const;

	// 一些接口
	// 获取x、y坐标
	double GetX() const;
	double GetY() const;
	
	// 虚函数
	// 以cout的方式输出（带提示）
	virtual void Show() const;	

	// 以cout的方式输出（不带提示）
	virtual void Show(bool, bool) const;

	// 以字符串的方式输出
	virtual std::string Show(std::string ) const;

protected:
	// 一些变量
	double x_p, y_p;
};

void test_CPoint();



