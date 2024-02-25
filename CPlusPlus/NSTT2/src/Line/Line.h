#pragma once

#include "../Point/Point.h"



class Line {
private:
    static constexpr double EPS = 2.2204460492503131e-16;

    double determinant(const Line &other) const;
    
public:
    double a{}, b{}, c{}; // Coefficients of the line equation: ax + by + c = 0

    Line(double a, double b, double c);

    Line(const Point &p1, const Point &p2);

    bool hasIntersection(const Line &other) const;

    Point findIntersection(const Line &other) const;

    Line findPerpendicular(const Point &p) const;
    bool isOrthogonal(const Line& other) const;
};
