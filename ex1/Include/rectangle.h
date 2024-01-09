#pragma once
#include "point.h"

//      //      CPoint 被初始化为矩形的左上角坐标

class CRectangle : public CPoint {
public:
    // 构造函数的两种重载
    CRectangle();

    CRectangle(const CPoint& );

    CRectangle(double x, double y, double w, double h);

    // 析构函数
    virtual ~CRectangle();

    // 重写基类虚函数
    virtual void Show() const override;

    // 获取矩形的面积
    double GetArea() const;

    // 获取矩形的周长
    double GetPerimeter() const;

private:
    // 矩形的宽
    double width;
    // 矩形的高
    double height;
};



void testCRectangle();