//
// Created by Roman on 16/02/2017.
//

#ifndef TIMGA_POINT_H
#define TIMGA_POINT_H
#include <algorithm>
#include <cmath>

const int SQUARE_SIZE = 3;

struct point {
    int x, y;
    point(int x = -1, int y = -1);
    point operator+(point other);
    point operator-(point other);
    bool inSquare(point p, int size = SQUARE_SIZE) const;
    bool operator!=(point other);
    static point INVALID_POINT;
};

bool operator<(point p, point ap);

inline int area (point a, point b, point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool intersect_1 (int a, int b, int c, int d) {
  if (a > b)  std::swap (a, b);
  if (c > d)  std::swap (c, d);
  return std::max(a,c) <= std::min(b,d);
}

bool intersect(point, point, point, point);

double dist(point, point);

#endif //TIMGA_POINT_H
