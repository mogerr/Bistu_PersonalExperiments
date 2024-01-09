#pragma once
#include "point.h"

//      //      CPoint ����ʼ��Ϊ���ε����Ͻ�����

class CRectangle : public CPoint {
public:
    // ���캯������������
    CRectangle();

    CRectangle(const CPoint& );

    CRectangle(double x, double y, double w, double h);

    // ��������
    virtual ~CRectangle();

    // ��д�����麯��
    virtual void Show() const override;

    // ��ȡ���ε����
    double GetArea() const;

    // ��ȡ���ε��ܳ�
    double GetPerimeter() const;

private:
    // ���εĿ�
    double width;
    // ���εĸ�
    double height;
};



void testCRectangle();