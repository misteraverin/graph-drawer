#include "point.h"
#include <algorithm>
#include <iostream>
//
// Created by Roman on 16/02/2017.
//

point point::INVALID_POINT = point(-1, -1);


point::point(int x, int y): x(x), y(y) {}


bool point::inSquare(point p, int size) const {

    return (std::min(x - p.x, y - p.y) >= 0) && (std::max(x - p.x, y - p.y) < size);
}

point point::operator+(point other) {
    return point(other.x + x, other.y + y);
}

point point::operator-(point other) {
    return point(x - other.x, y - other.y);
}


bool point::operator!=(point other) {
    return (x != other.x || y != other.y);
}


bool operator<(point p, point ap) {
    return std::make_pair(p.x, p.y) < std::make_pair(ap.x, ap.y);
}


bool intersect (point a, point b, point c, point d) {
  return intersect_1 (a.x, b.x, c.x, d.x)
    && intersect_1 (a.y, b.y, c.y, d.y)
    && area(a,b,c) * area(a,b,d) <= 0
    && area(c,d,a) * area(c,d,b) <= 0;
}

double dist(point a, point b){
  return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

