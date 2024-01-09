#pragma once
#include "point.h"

class CCircle : public CPoint {
public:
    // ���캯������������
    CCircle();

    CCircle(double x, double y, double r);

    CCircle(const CPoint& p, double r);

    // ��������
    virtual ~CCircle();

    // ��д�����麯��
    virtual void Show() const override;

    // ��ȡԲ�����
    double GetArea() const;

    // ��ȡ�뾶
    double GetRadius() const;

    // ��ȡԲ������
    double GetCenterX() const;
    double GetCenterY() const;

    // ��ȡԲ���ܳ�
    double GetPerimeter() const;

private:
    // �뾶
    double radius;
};

void testCCircle();