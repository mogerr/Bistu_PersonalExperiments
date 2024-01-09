// #include "stdafx.h"
#include "circular.h"

using namespace std;


// ���캯������������
CCircle::CCircle() : CPoint(), radius(0.0) 
{

}

CCircle::CCircle(double x, double y, double r) : CPoint(x, y), radius(r)
{

}

CCircle::CCircle(const CPoint& p, double r) : CPoint(p), radius(r)
{

}

// ��������
CCircle::~CCircle() {
    //std::cout << "Circle destructor called." << std::endl;
}

void CCircle::Show() const {
    // ���û���� Show ����
    std::cout << "Բ�� of Circle: "; CPoint::Show(true, true); std::cout << std::endl;
    std::cout << "�뾶 of Circle: " << radius << std::endl;
    std::cout << "��� of Circle: " << CCircle::GetArea() << std::endl;
    std::cout << "�ܳ� of circle: " << CCircle::GetPerimeter() << std::endl;
}

// ��ȡԲ�����
double CCircle::GetArea() const {
    return 3.14159 * radius * radius;
}

// ��ȡ�뾶
double CCircle::GetRadius() const {
    return radius;
}

// ��ȡԲ������
double CCircle::GetCenterX() const {
    return GetX();}
double CCircle::GetCenterY() const {
    return GetY();}


// ��ȡԲ���ܳ�
double CCircle::GetPerimeter() const {
    return 2.0 * 3.14159 * radius;
}






void testCCircle() {

    std::cout << endl << "���� testCCircle() ����" << endl;

    // ����CCircle���󣬲��������ֹ��캯��
    CPoint  point;
    CCircle circle1(point,4);
    CCircle circle2(3.0, 4.0, 2.5);

    // �����麯�� Show �������������
    circle1.Show();

    // ��ȡԲ�İ뾶��Բ��������ܳ�����ӡ
    std::cout << std::endl;
    std::cout << "Բ�� of circle_2: (" << circle2.GetCenterX() << ", " << circle2.GetCenterY() << ")" << std::endl;
    std::cout << "�뾶 of circle_2: " << circle2.GetRadius() << std::endl;
    std::cout << "�ܳ� of circle_2: " << circle2.GetPerimeter() << std::endl;
    std::cout << std::endl;
}