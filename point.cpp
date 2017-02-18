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
