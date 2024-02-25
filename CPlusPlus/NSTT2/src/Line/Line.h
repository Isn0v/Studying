//
// Created by bogdan on 22.02.24.
//
#include "../Point/Point.h"

#ifndef C_KREST_KREST_LINE_H
#define C_KREST_KREST_LINE_H

class Line {
public:
    double a{}, b{}, c{}; // Coefficients of the line equation: ax + by + c = 0

    Line(double a, double b, double c);

    Line(const Point &p1, const Point &p2);

    bool hasIntersection(const Line &other) const;

    Point findIntersection(const Line &other) const;

    Line findPerpendicular(const Point &p) const;
    bool isOrthogonal(const Line& other) const;
};


#endif //C_KREST_KREST_LINE_H
