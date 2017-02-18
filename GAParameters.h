//
// Created by Roman on 17/02/2017.
//

#ifndef TIMGA_GAPARAMETERS_H
#define TIMGA_GAPARAMETERS_H

#include <array>

struct GAParameters {
    int reproducibleSize;
    int crossoverRate;
    int mutationRate;
    // for linear normalization
    int step;
    int largestValue;

    int iterNumber;
    int maxPopulationSize;
    // grid size
    int N;
    // square size
    int SQUARE_SIZE;
    std::array<float, 5> COEFS;

    GAParameters(const int N = 40, const int SQUARE_SIZE = 3, const std::array<float, 5> COEFS = {2.f, -2.f, -2.5f, 0.25f, -1.f});
//    GAParameters();
};


#endif //TIMGA_GAPARAMETERS_H
