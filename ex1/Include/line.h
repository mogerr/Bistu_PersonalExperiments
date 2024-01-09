#pragma once
#include "point.h"
#include "math.h"

class CLine : public CPoint {
public:
    // 构造函数的两种重载
    CLine();


    CLine(double x1, double y1, double x2, double y2);

    // 析构函数
    ~CLine();

    // 重写基类虚函数
    virtual void Show() const override;

    // 获取长度
    double getlength() const;

private:
    double endX;
    double endY;
    double length;

    // 计算线段长度
    void CalculateLength();   

};

void testCLine();