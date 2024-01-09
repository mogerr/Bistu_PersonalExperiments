
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


// ���� - �����
CPoint CPoint::operator-(const CPoint& other) const {
	return CPoint(   x_p - other.x_p,    y_p - other.y_p   );
}

// ���� + �����
CPoint CPoint::operator+(const CPoint& other) const {
	return CPoint(	x_p + other.x_p,	 y_p + other.y_p);
}

// ��cout�ķ�ʽ���������ʾ��
void CPoint::Show() const
{
	cout << "�õ�Ķ�ά�ѿ�������Ϊ: ";
	cout << "(" << x_p << "," << y_p << ")" << endl;
}

// ��cout�ķ�ʽ�����������ʾ��
void CPoint::Show(bool x, bool  y)const {
	cout << "(" << x_p << "," << y_p << ")";
}

// ���ַ����ķ�ʽ���
std::string CPoint::Show(std::string preStr) const  {
	return preStr + "(" + std::to_string(x_p) + "," + std::to_string(y_p) + ")";
}




/**
 * @brief  ��������� -  + ���Ժ���
 * @return 
 */
void test_CPoint() {

	cout << endl << "���� test_CPoint() ������" << endl;

    CPoint point1(3.0, 4.0);
    CPoint point2(1.0, 2.0);

	// ��ӡ���
	point1.Show();
	point2.Show();

    // ʹ�� - �����
    CPoint result1 = point1 - point2;

    // ��ӡ���
    //result1.Show();
	cout << result1.Show("") << "=" << point1.Show("") << "-" << point2.Show("") << endl;

	// ʹ�� + �����
    CPoint result2 = point1 + point2;

    // ��ӡ���
    result2.Show();
	cout << result2.Show("") << "=" << point1.Show("") << "+" << point2.Show("") << endl <<endl;
}