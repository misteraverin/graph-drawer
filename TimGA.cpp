//
// Created by Roman on 17/02/2017.
//

#include "TimGA.h"

bool cmpIndividuals(Individual individual1, Individual individual2) {
    return individual1.fitness() < individual2.fitness();
}

void TimGA::evolve() {
    std::vector<Individual> population;
    for (int i = 0; i < parameters.maxPopulationSize; ++i) {
        population.push_back(Individual(adjacencyList));
    }
    for (int iter = 0; iter < parameters.iterNumber; ++iter) {
        std::sort(population.begin(), population.end(), cmpIndividuals);
        if (iter != 0) {
            for (int i = 0; i < population.size() - parameters.maxPopulationSize; ++i) {
                population.pop_back();
            }
        }
        std::vector<int> valuePartialSums;
        if (rand() % 100 < 5) {
            valuePartialSums.push_back(parameters.largestValue);
            for (int k = 1; k < population.size(); ++k) {
                valuePartialSums.push_back(parameters.largestValue - k * parameters.step
                                           + valuePartialSums[k - 1]);
            }
            int rn = rand() % valuePartialSums[valuePartialSums.size() - 1];
            int index = std::upper_bound(valuePartialSums.begin(), valuePartialSums.end(), rn) - valuePartialSums.begin();
            Individual parent1 = population[index];
            for (int k = index; k < population.size(); ++k) {
                population[k] = population[k + 1];
            }
            valuePartialSums.pop_back();
            rn  = rand() % valuePartialSums[valuePartialSums.size() - 1];
            int aIndex = std::upper_bound(valuePartialSums.begin(), valuePartialSums.end(), rn) - valuePartialSums.begin();
            if (aIndex >= index)
                ++aIndex;

            Individual parent2 = population[aIndex];
            if (rand() % 2) {
                population.push_back(rectCrossover(parent1, parent2).first);
                population.push_back(rectCrossover(parent1, parent2).second);
            }
            else {
                population.push_back(threeNodesCrossover(parent1, parent2).first);
                population.push_back(threeNodesCrossover(parent1, parent2).second);
            }
        }
        else {
            valuePartialSums.push_back(parameters.largestValue);
            for (int k = 1; k < population.size(); ++k) {
                valuePartialSums.push_back(parameters.largestValue - k * parameters.step + valuePartialSums[k - 1]);
            }
            int rn = rand() % valuePartialSums[valuePartialSums.size() - 1];
            int index = std::upper_bound(valuePartialSums.begin(), valuePartialSums.end(), rn) - valuePartialSums.begin();
            Individual ind = population[index];
            int x = rand() % 4;
            if (x == 0)
                ind.singleMutate();
            if (x == 1)
                ind.smallMutate();
            if (x == 2)
                ind.edgeMutate1();
            if (x == 3)
                ind.edgeMutate2();
        }
    }

}

void TimGA::setGraph(std::shared_ptr<std::vector<std::vector<int>>> adj) {
    adjacencyList = adj;
}

void TimGA::setParameters(GAParameters parameters) {
    this->parameters = parameters;
}
