//
// Created by Roman on 17/02/2017.
//

#include "TimGA.h"

bool cmpIndividuals(Individual individual1, Individual individual2) {
    return individual1.fitness() < individual2.fitness();
}

Individual TimGA::evolve() {
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
        std::vector<int> probs;
        for (int m = 0; m < population.size(); ++m) {
            probs.push_back(parameters.largestValue - m * parameters.step);
        }
        std::pair<int, int> p = getRandomPair(probs);
        Individual parent1 = population[p.first];
        Individual parent2 = population[p.second];
        if (rand() % 100 < parameters.crossoverRate) {

            if (rand() % 2) {
                population.push_back(rectCrossover(parent1, parent2).first);
                population.push_back(rectCrossover(parent1, parent2).second);
            }
            else {
                population.push_back(threeNodesCrossover(parent1, parent2).first);
                population.push_back(threeNodesCrossover(parent1, parent2).second);
            }
        }
        valuePartialSums.push_back(parameters.largestValue);
        for (int k = 1; k < population.size(); ++k) {
            valuePartialSums.push_back(parameters.largestValue - k * parameters.step + valuePartialSums[k - 1]);
        }
        int rn = rand() % valuePartialSums[valuePartialSums.size() - 1];
        int index = std::upper_bound(valuePartialSums.begin(), valuePartialSums.end(), rn) - valuePartialSums.begin();
        Individual ind = population[index];
        if (rand() % 100 < parameters.mutationRate) {
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
    return population[0];
}

void TimGA::setGraph(std::shared_ptr<std::vector<std::vector<int>>> adj) {
    adjacencyList = adj;
}

void TimGA::setParameters(GAParameters parameters) {
    this->parameters = parameters;
}

std::pair<int, int> TimGA::getRandomPair(std::vector<int> &probs) {
    std::vector<int> probPartialSums;
    for (int k = 0; k < probs.size(); ++k) {
        probPartialSums.push_back(k == 0 ? probs[0] : probs[k] + probPartialSums[k - 1]);
    }
    int rn = rand() % probPartialSums[probPartialSums.size() - 1];
    int index = std::upper_bound(probPartialSums.begin(), probPartialSums.end(), rn) - probPartialSums.begin();
    for (int k = index; k < probPartialSums.size(); ++k) {
        probPartialSums[k] = probPartialSums[k + 1] - probs[index];
    }
    probPartialSums.pop_back();
    rn = rand() % probPartialSums[probPartialSums.size() - 1];
    int aIndex = std::upper_bound(probPartialSums.begin(), probPartialSums.end(), rn) - probPartialSums.begin();
    if (aIndex >= index)
        ++aIndex;
    return std::pair<int, int>(index, aIndex);
}

