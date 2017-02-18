#include <iostream>
#include <assert.h>
#include "Individual.h"

using namespace std;

#define MAXN int(1e3 + 10)
#define INF int(1e9)
#define pb push_back
#define mp make_pair
#define sz(A) (int)(A).size()
#define sqr(a) ((a) * (a))


const int SIZE_POPULATION = 10;
const int SIZE_SQUARE = 40;
const int NUMBER_VERTEX = 60;



bool Individual::isPositionFree(point p) {
    return p.x >= 0 && p.x < N && p.y >= 0 && p.y < N && (matrix[p.x][p.y] == -1);
}

std::pair<Individual, Individual> rectCrossover(Individual parent1, Individual parent2) {
    int validXsNumber = N - SQUARE_SIZE + 1;
    int randNum = rand() % (validXsNumber * validXsNumber);
    printf("%d\n", randNum);
    point parentSquareCorner(randNum % validXsNumber, randNum / validXsNumber);
//    point parentSquareCorner(0, 0);
    randNum = rand() % (validXsNumber * validXsNumber);
    printf("%d\n", randNum);
    point childSquareCorner(randNum % validXsNumber, randNum / validXsNumber);
//    point childSquareCorner(1, 0);
    std::set<int> parent1SquareVertices;
    std::set<int> parent2SquareVertices;
    std::set<int> child1SquareVertices;
    std::set<int> child2SquareVertices;
    for (int i = 0; i < parent1.vertexNumber; ++i) {
        if (parent1.positions[i].inSquare(parentSquareCorner))
            parent1SquareVertices.insert(i);
        if (parent2.positions[i].inSquare(parentSquareCorner))
            parent2SquareVertices.insert(i);
        if (parent1.positions[i].inSquare(childSquareCorner))
            child1SquareVertices.insert(i);
        if (parent2.positions[i].inSquare(childSquareCorner))
            child2SquareVertices.insert(i);
    }
    Individual child1 = parent1;
    Individual child2 = parent2;
    // clear child rectangles
    child1.clearRectangle(child1SquareVertices, parent2, childSquareCorner);
    child2.clearRectangle(child2SquareVertices, parent1, childSquareCorner);
    // move vertices from parent rects to cleared rects
    for (auto it = parent2SquareVertices.begin(); it != parent2SquareVertices.end(); ++it) {
        child1.changePosition(*it, parent2.positions[*it] + childSquareCorner - parentSquareCorner);
    }
    for (auto it = parent1SquareVertices.begin(); it != parent1SquareVertices.end(); ++it) {
        child2.changePosition(*it, parent1.positions[*it] + childSquareCorner - parentSquareCorner);
    }
    return std::make_pair(child1, child2);
}


std::pair<Individual, Individual> threeNodesCrossover(Individual parent1, Individual parent2) {
    Individual child1 = parent1;
    Individual child2 = parent2;
    // vertices of degree >= 2
    std::vector<int> validVertices;
    for (int i = 0; i < child1.adjacencyList->size(); ++i) {
        if (child1.adjacencyList->at(i).size() >= 2)
            validVertices.push_back(i);
    }
    if (!validVertices.empty()) {
        std::cout << "there're some valid nodes" << std::endl;
        int v = rand() % validVertices.size();
        int index = rand() % child1.adjacencyList->at(v).size();
        int u = (*child1.adjacencyList)[v][index];
        int aIndex = rand() % (child1.adjacencyList->at(v).size() - 1);
        if (aIndex >= index) ++aIndex;
        int w = (*child1.adjacencyList)[v][aIndex];
        std::cout << "nodes to perform three nodes crossover on: " << u << ' ' << v << ' ' << w << std::endl;
        if (child1.isPositionFree(parent2.positions[u]) && child1.isPositionFree(parent2.positions[v])
            && child1.isPositionFree(parent2.positions[w])) {
            child1.changePosition(u, parent2.positions[u]);
            child1.changePosition(v, parent2.positions[v]);
            child1.changePosition(w, parent2.positions[w]);
        }
        if (child2.isPositionFree(parent1.positions[u]) && child2.isPositionFree(parent1.positions[v])
            && child2.isPositionFree(parent1.positions[w])) {
            child2.changePosition(u, parent1.positions[u]);
            child2.changePosition(v, parent1.positions[v]);
            child2.changePosition(w, parent1.positions[w]);
        }
    }
    return std::pair<Individual, Individual>(child1, child2);
}


void Individual::clearRectangle(std::set<int> childSquareVertices, Individual otherParent, point rect) {
    for (auto it = childSquareVertices.begin(); it != childSquareVertices.end(); ++it) {
        int vertex = *it;
        point posInOtherParent = otherParent.positions[vertex];
        if (matrix[posInOtherParent.x][posInOtherParent.y] == -1 && !posInOtherParent.inSquare(rect)) {
            changePosition(vertex, posInOtherParent);
        }
        else {
            point freeCell = getFreeCellOutsideRect(rect);
            if (freeCell != point::INVALID_POINT) {
                changePosition(vertex, freeCell);
            }
            else {
                std::cout << "No free cells\n";
            }
        }
    }
}


bool Individual::changePosition(int vertex, point p) {
    point oldPosition = positions[vertex];
    if (oldPosition != p && p != point::INVALID_POINT) {
        positions[vertex] = p;
        freeCells.insert(oldPosition);
        freeCells.erase(p);
        matrix[oldPosition.x][oldPosition.y] = -1;
        matrix[p.x][p.y] = vertex;
        return 1;
    }
    return 0;
}

void Individual::initMatrix() {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            matrix[i][k] = -1;
            freeCells.insert(point(i, k));
        }
    }
}

Individual::Individual(std::vector<point> positions, std::shared_ptr<std::vector<std::vector<int>>> adj) {
    this->positions = positions;
    vertexNumber = positions.size();
    initMatrix();
    adjacencyList = adj;
    for (int i = 0; i < vertexNumber; ++i) {
        matrix[positions[i].x][positions[i].y] = i;
//        std::cout << std::boolalpha << (freeCells.find(point(positions[i].x, positions[i].y)) != freeCells.end()) << std::endl;
        freeCells.erase(point(positions[i].x, positions[i].y));
        degPartialSums.push_back(i > 0 ? degPartialSums[i - 1] + (*adj)[i].size() : (*adj)[0].size());
    }
    edgeNumber = 0;
    for (int i = 0; i < vertexNumber; ++i) {
        for (int j = 0; j < (*adj)[i].size(); ++j) {
            int v = (*adj)[i][j];
            std::cout << (*adj)[i][j] << ' ';
            if (v < i)
                ++edgeNumber;
        }
        std::cout << std::endl;
    }
//    this->params = parameters;
}

Individual::Individual(std::shared_ptr<std::vector<std::vector<int>>> adj) {
    this->vertexNumber = adj->size();
    // randomly generate positions
    positions.resize(vertexNumber);
    std::set<int> unusedVertices;
    for (int i = 0; i < vertexNumber; ++i) {
        unusedVertices.insert(i);
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            freeCells.insert(point(i, j));
        }

    }
    initMatrix();
    for (int i = 0; i < vertexNumber; ++i) {
        if (!freeCells.empty() && !unusedVertices.empty()) {
            int cellIndex = rand() % ((int) freeCells.size());
            int vertexIndex = rand() % ((int) unusedVertices.size());
            std::set<point>::iterator cellIter = freeCells.begin();
            std::advance(cellIter, cellIndex);
            auto vertexIter = unusedVertices.begin();
            std::advance(vertexIter, vertexIndex);
            positions[*vertexIter] = *cellIter;
            matrix[cellIter->x][cellIter->y] = *vertexIter;
            freeCells.erase(cellIter);
            unusedVertices.erase(vertexIter);
        }
    }

}

#ifdef DEBUG


void Individual::testChangePosition() {
    std::cout << std::endl;
    out();
    int newX = rand() % N;
    int newY = rand() % N;
    std::cout << "change position of vertex 0" << ' ' << "from "
    << positions[0].x << ' ' << positions[0].y << " to " << newX << ' ' << newY << std::endl;
    changePosition(0, point(newX, newY));
    out();
}

void Individual::out() {
    std::cout << "vertex number " << vertexNumber << std::endl;
    std::cout << "matrix: " << std::endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {

            std::cout << matrix[j][i] + 1 << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "positions: " << std::endl;
    for (int i = 0; i < vertexNumber; ++i) {
        std::cout << positions.at((size_t) i).x << ' ' << positions[i].y << std::endl;
    }
    std::cout << std::endl;
    std::cout << "free cells: " << std::endl;
    std::cout << "size=" << freeCells.size() << std::endl;
//    for (auto it = freeCells.begin(); it != freeCells.end(); ++it) {
//        std::cout << it->x << ' ' << it->y << std::endl;
//    }
}

#endif

point Individual::getFreeCellOutsideRect(point rectCorner) {
    for (auto it = freeCells.begin(); it != freeCells.end(); ++it) {
        if (!it->inSquare(rectCorner))
            return *it;
    }
    return point::INVALID_POINT;
}

point Individual::getRandomFreeCell() {
    if (freeCells.size()) {
        int cellIndex = rand() % ((int) freeCells.size());
        auto cellIter = freeCells.begin();
        std::advance(cellIter, cellIndex);
        return *cellIter;
    }
    return point::INVALID_POINT;
}

void Individual::singleMutate() {
    int vertex = rand() % vertexNumber;
    std::cout << "moved vertex " << vertex << std::endl;
    changePosition(vertex, getRandomFreeCell());
}


void Individual::smallMutate() {
    // divisor is number of all pairs of cells that contain >= 1 vertex
    int rn = rand() % (freeCells.size() * vertexNumber + vertexNumber * (vertexNumber - 1) / 2);
    if (rn >= freeCells.size() * vertexNumber) {
        // both contain vertices
        int pairIndex = rn - freeCells.size() * vertexNumber;
        int vertex = 2 * pairIndex % (vertexNumber - 1);
        int aVertex = 2 * pairIndex / vertexNumber;
        std::cout << "swap vertices " << vertex << ' ' << aVertex << std::endl;
        if (vertex >= aVertex) {
            ++vertex;
        }
        std::swap(positions[vertex], positions[aVertex]);
        std::swap(matrix[positions[vertex].x][positions[vertex].y], matrix[positions[aVertex].x][positions[aVertex].y]);
    }
    else {
        // one is free
        int vertex = rn % vertexNumber;
        int freeCellIndex = rn / vertexNumber;
        auto it = freeCells.begin();
        std::advance(it, freeCellIndex);
        changePosition(vertex, *it);
        std::cout << "free cell " << it->x << ' ' << it->y << ' ' << "vertex " << vertex << std::endl;
    }
}

void Individual::edgeMutate1() {
    std::pair<int, int> edge = getRandomEdge();
    int vertex = edge.first;
    int aVertex = edge.second;
#ifdef  DEBUG
    printf("chosen edge %d %d for edge mutate 1\n", vertex, aVertex);
#endif
    if (vertex != -1) {
        // choose pair of free cells
        int cellIndex = rand() % (freeCells.size() - 1);
        int aCellIndex = rand() % freeCells.size();
        if (cellIndex >= aCellIndex) ++cellIndex;
        auto iter = freeCells.begin();
        std::advance(iter, cellIndex);
        auto aIter = freeCells.begin();
        std::advance(aIter, aCellIndex);
        if (iter != freeCells.end())
            changePosition(vertex, *iter);
        if (aIter != freeCells.end())
            changePosition(aVertex, *aIter);
    }
}

// translate an edge

void Individual::edgeMutate2() {
    std::pair<int, int> edge = getRandomEdge();
    int aVertex = edge.second;
    int vertex = edge.first;
#ifdef  DEBUG
    printf("chosen edge %d %d for edge mutate 2\n", vertex, aVertex);
#endif

    point p = point::INVALID_POINT;
    if (vertex != -1) {
        for (auto it = freeCells.begin(); it != freeCells.end(); ++it) {
            p = *it;
            if (isPositionFree(p + positions[aVertex] - positions[vertex])) {
                break;
            }
        }
        point oldP = positions[vertex];
//        std::cout << "new position " << p.x << ' ' << p.y << std::endl;
//        std::cout << "diff between positions " <<
//                (positions[aVertex] - positions[vertex]).x << (positions[aVertex] - positions[vertex]).y << std::endl;
        if (changePosition(vertex, p)) {
            point ap = p + positions[aVertex] - oldP;
            changePosition(aVertex, ap);
        }
    }
}

void Individual::twoEdgesMutate() {

}

std::pair<int, int> Individual::getRandomEdge() {
    // choose pair of vertices that are connected with edge
    int rn = rand() % degPartialSums[vertexNumber - 1];
    auto it = std::upper_bound(degPartialSums.begin(), degPartialSums.end(), rn);
    if (it != degPartialSums.end()) {
        int vertex = it - degPartialSums.begin();
        int index;
        if (vertex == 0)
            index = rn;
        else
            index = rn - degPartialSums[vertex - 1];
        if(index < 0 || (*adjacencyList)[vertex].size() <= index) {
            std::cout << "index " << index << std::endl;
            assert(false);
        }
        return std::make_pair(vertex, (*adjacencyList)[vertex][index]);
    }
    return std::pair<int, int>(-1, -1);
}

// set double sum_min_dist
void Individual:: minimum_node_distance_sum(){
  double sum_min_dist = 0;
  double global_min_edge = INF;
  std::vector<double> min_dist;
  min_dist.resize(vertexNumber);
  for(int i = 0; i < vertexNumber; i++){
    double min_dist_node = INF;
    for(int j = 0; j < (*adjacencyList)[i].size(); j++){
      int u = (*adjacencyList)[i][j];
      int v = i;
      min_dist_node = min(min_dist_node, dist(positions[u], positions[v]));
    }
    if(min_dist_node >= INF)  continue;
    else{
      sum_min_dist += min_dist_node;
      min_dist[i] = min_dist_node;
      global_min_edge = min(min_dist_node, global_min_edge);
    }
  }
  minimum_dist_sum = sum_min_dist;
  min_edge = global_min_edge;
}

void Individual:: minimum_node_distance(){
  min_dist_node = vertexNumber *  min_edge * min_edge;
}


void Individual::edge_length_deviation(){
  double sum = 0;
  for (int u = 0; u < vertexNumber; ++u)
      for (size_t j = 0; j < (*adjacencyList)[u].size(); ++j) {
          int v = (*adjacencyList)[u][j];
          double length = dist(positions[u], positions[v]);
          sum += (length - min_edge) *  (length - min_edge);
      }
  deviation = sqrt(sum * 1.0 / double(edgeNumber));
}


void Individual::number_crossings(){
   int cnt_crossings = 0;
   for (int u = 0; u < vertexNumber; ++u) {
       for (size_t j = 0; j < (*adjacencyList)[u].size(); ++j) {
           int v = (*adjacencyList)[u][j];
           if (u < v) {
               for (int u1 = 0; u1 < vertexNumber; ++u1)
                   for (size_t k = 0; k < (*adjacencyList)[u1].size(); ++k) {
                       int v1 = (*adjacencyList)[u1][j];
                        cnt_crossings += intersect(positions[u], positions[v], positions[u1], positions[v1]);
                   }
           }
       }
   }
   crossings = cnt_crossings;
}


double Individual::fitness() {
    minimum_node_distance_sum();
    minimum_node_distance();
    edge_length_deviation();
    number_crossings();
    double expr = 2 * minimum_dist_sum;
    expr += (-2) * deviation;
    expr += (-2.5) * (deviation/min_dist_node);
    expr += (0.25) * (vertexNumber * min_dist_node * min_dist_node);
    expr -= (crossings * N * N);
    return expr;
}
