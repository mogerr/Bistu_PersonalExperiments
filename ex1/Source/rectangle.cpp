// #include "stdafx.h"
#include "rectangle.h"
#include "math.h"

using namespace std;

// ���캯������������
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

// ��������
CRectangle::~CRectangle() {
	//std::cout << "Rectangle destructor called." << std::endl;
}


// ��д�����麯��
void CRectangle::Show() const {
	// ���û���� Show ����
	std::cout << "�������Ͻǵ�����: ";  CPoint::Show(true, true);  std::cout << std::endl;
	std::cout << "���ε� width : " << width << ", height: " << height << std::endl;
}

// ��ȡ���ε����
double CRectangle::GetArea() const {
	return width * height;
}

// ��ȡ���ε��ܳ�
double CRectangle::GetPerimeter() const {
	return 2.0 * (width + height);
}



void testCRectangle()
{
	std::cout << endl << "���� testCRectangle() ����" << endl;

	// ����CRectangle���󣬲��������ֹ��캯��
	CRectangle rectangle1;
	CRectangle rectangle2(1.0, 2.0, 3.0, 4.0);

	// �����麯�� Show �������������
	rectangle1.Show();
	std::cout << std::endl;
	rectangle2.Show();

	// ��ȡ���ε�������ܳ�����ӡ
	std::cout << "���ε����: " << rectangle2.GetArea() << std::endl;
	std::cout << "���ε��ܳ�: " << rectangle2.GetPerimeter() << std::endl << std::endl;
}