#include "parabola.h"
#include "iostream"
#include <vector>

using namespace std;


CParabola::CParabola(double a, double b, double c) 
    : CPoint(), a_coefficient(a), b_coefficient(b), c_coefficient(c) 
{}

CParabola::~CParabola() {
    //std::cout << "Parabola destructor called." << std::endl;
}


void CParabola::Show() const {
    //CPoint::Show();
    std::cout << "Parabola equation: " << a_coefficient << "x^2 + " << b_coefficient << "x + " << c_coefficient << std::endl;
    std::cout << "Vertex coordinates: (" << GetVertexX() << ", " << GetVertexY() << ")" << std::endl;
    std::cout << "Focus coordinates: (" << GetFocusX() << ", " << GetFocusY() << ")" << std::endl;
}

double CParabola::GetVertexX() const {
    return -b_coefficient / (2 * a_coefficient);
}

double CParabola::GetVertexY() const {
    return c_coefficient - (b_coefficient * b_coefficient) / (4 * a_coefficient);
}

double CParabola::GetFocusX() const {
    return GetVertexX();
}

double CParabola::GetFocusY() const {
    return GetVertexY() + 1 / (4 * a_coefficient);
}




void testCParabola() {

    std::cout << endl << "这是 testCParabola() 函数" << endl;

    // 创建CParabola对象
    CParabola parabola(1.0, -2.0, 1.0);

    // 调用虚函数 Show 来输出几何特征
    parabola.Show();

    std::cout << endl;
}



