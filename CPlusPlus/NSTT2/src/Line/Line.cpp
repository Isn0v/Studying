//
// Created by bogdan on 22.02.24.
//
#include <cmath>
#include "Line.h"
const double EPS = 2.2204460492503131e-16;
bool Line::hasIntersection(const Line &other) const {
    double det = a * other.b - other.a * b;
    return std::abs(det) > EPS; // If det is not equal to 0, the lines intersect
}

Line::Line(const Point &p1, const Point &p2) {
    a = -(p2.y - p1.y);
    b = p2.x - p1.x;
    c = p2.y * (p2.x-p1.x) - p2.x*(p2.y-p1.y);
}

Line::Line(double a_, double b_, double c_) {
    a=a_;
    b=b_;
    c=c_;
}

Point Line::findIntersection(const Line &other) const {
    double det = a * other.b - other.a * b;
    double x = (other.b * c - b * other.c) / det;
    double y = (a * other.c - other.a * c) / det;
    return {x, y};
}

Line Line::findPerpendicular(const Point &p) const {
    double newA = -b;
    double newB = a;
    double newC = -newA * p.x - newB * p.y;
    return {newA, newB, newC};
}
bool Line::isOrthogonal(const Line& other) const {
    return (a * other.a + b * other.b) == 0; // Check if the dot product of the direction vectors is zero
}
