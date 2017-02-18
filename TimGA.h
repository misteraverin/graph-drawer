//
// Created by Roman on 17/02/2017.
//

#ifndef TIMGA_TIMGA_H
#define TIMGA_TIMGA_H

#include <vector>
#include <memory>

#include "GAParameters.h"
#include "Individual.h"

bool cmpIndividuals(Individual, Individual);
class TimGA {
    static std::pair<int, int> getRandomPair(std::vector<int>& probs);
    GAParameters parameters;
    std::shared_ptr<std::vector<std::vector<int>>> adjacencyList;
public:
    void setParameters(GAParameters);
    void setGraph(std::shared_ptr<std::vector<std::vector<int>>>);
    Individual evolve();
};


#endif //TIMGA_TIMGA_H
