#pragma once
#include "point.h"

class CCircle : public CPoint {
public:
    // 构造函数的三种重载
    CCircle();

    CCircle(double x, double y, double r);

    CCircle(const CPoint& p, double r);

    // 析构函数
    virtual ~CCircle();

    // 重写基类虚函数
    virtual void Show() const override;

    // 获取圆的面积
    double GetArea() const;

    // 获取半径
    double GetRadius() const;

    // 获取圆心坐标
    double GetCenterX() const;
    double GetCenterY() const;

    // 获取圆的周长
    double GetPerimeter() const;

private:
    // 半径
    double radius;
};

void testCCircle();