
#include "line.h"

using namespace std;

CLine::CLine() : CPoint(), length(0.0), endX(0.0), endY(0.0) 
{

}

CLine:: CLine(double x1, double y1, double x2, double y2)
    : CPoint(x1, y1), endX(x2), endY(y2) {
    CalculateLength();
}

// ��������
CLine::~CLine() {
    //std::cout << "Line destructor called." << std::endl;
}

// ��д�����麯��
void CLine::Show() const {
    std::cout << "����һ����  ";
    // ���û���� Show ����
    std::cout << CPoint::Show("���: ") ; 
    std::cout << "  �յ�: (" << CLine::endX  << "," << CLine::endY << ")" << std::endl;
    std::cout << "Line length: " <<  CLine::getlength()  << std::endl;
}

// �����߶γ���
void CLine::CalculateLength() {
    CLine::length = std::sqrt(std::pow(endX - x_p, 2) + std::pow(endY - y_p, 2));
}

// ��ȡ����
double CLine::getlength() const {
    return CLine::length;
}


void testCLine() {

    std::cout << endl << "���� testCLine() ����" << endl;

    // ����CLine���󣬲��������ֹ��캯��
    CLine line1;
    CLine line2(1.0, 2.0, 4.0, 6.0);

    // �����麯�� Show �������������
    line1.Show();
    line2.Show();

    std::cout << endl;
}