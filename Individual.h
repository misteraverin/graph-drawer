#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <random>
#include <iostream>
#include <memory>
#include "point.h"
#include "GAParameters.h"

#define DEBUG 1

#ifdef DEBUG
const int N = 9;
#else
const int N = 40;
#endif

class Individual {
    int vertexNumber;
	std::shared_ptr<std::vector<std::vector<int>>> adjacencyList;
	std::vector<int> degPartialSums;
	int matrix[N][N];
	std::set<point> freeCells;
	std::vector<point> positions;
	GAParameters params;
	bool changePosition(int vertex, point p);
	bool isPositionFree(point p);
	void initMatrix();
	point getFreeCellOutsideRect(point);
	void clearRectangle(std::set<int>, Individual, point);
	point getRandomFreeCell();
	std::pair<int, int> getRandomEdge();
public:
	Individual(std::vector<point> positions, std::shared_ptr<std::vector<std::vector<int>>> adj);
	Individual(std::shared_ptr<std::vector<std::vector<int>>> adj);
	double fitness();
	void singleMutate();
	void smallMutate();
	void edgeMutate1();
	void edgeMutate2();
	void twoEdgesMutate();

	friend std::pair<Individual, Individual> rectCrossover(Individual, Individual);
	friend std::pair<Individual, Individual> threeNodesCrossover(Individual, Individual);
#ifdef DEBUG
	void testChangePosition();
	void out();

#endif
};




#endif // CHROMOSOME_H

