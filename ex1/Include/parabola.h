#pragma once
#include "point.h"



class CParabola : public CPoint {
public:
    CParabola(double a, double b, double c);
    virtual ~CParabola();

    // ÖØÐ´
    virtual void Show() const override;

    double GetVertexX() const;

    double GetVertexY() const;

    double GetFocusX() const;

    double GetFocusY() const;

private:
    double a_coefficient;
    double b_coefficient;
    double c_coefficient;
};


void testCParabola();








