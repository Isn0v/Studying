#include <cmath>
#include "Line.h"
bool Line::hasIntersection(const Line &other) const
{
    return std::abs(determinant(other)) > EPS;
}

Line::Line(const Point &p1, const Point &p2)
    : a(-(p2.y - p1.y)),
      b(p2.x - p1.x),
      c(p2.y * (p2.x - p1.x) - p2.x * (p2.y - p1.y))
{
}

double Line::determinant(const Line &other) const
{
    return a * other.b - other.a * b;
}

Line::Line(double a_, double b_, double c_)
{
    a = a_;
    b = b_;
    c = c_;
}

Point Line::findIntersection(const Line &other) const
{
    double det = determinant(other);
    double x = (other.b * c - b * other.c) / det;
    double y = (a * other.c - other.a * c) / det;
    return {x, y};
}

Line Line::findPerpendicular(const Point &p) const
{
    double newA = -b;
    double newB = a;
    double newC = -newA * p.x - newB * p.y;
    return {newA, newB, newC};
}

bool Line::isOrthogonal(const Line &other) const
{
    double dotProduct = a * other.a + b * other.b;
    return std::abs(dotProduct) < EPS;
}