//
// Created by Roman on 16/02/2017.
//

#ifndef TIMGA_POINT_H
#define TIMGA_POINT_H


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


#endif //TIMGA_POINT_H
