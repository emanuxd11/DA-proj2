#ifndef DA_PROJ2_NEARESTNEIGHBOR_H
#define DA_PROJ2_NEARESTNEIGHBOR_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "../includes/Graph.h"

class NearestNeighbor {
public:
    NearestNeighbor(Graph g);

    bool run();

protected:
    bool calculateTour(int idx);

    long double distance = 0;
    std::string order;
    Graph graph;
};

#endif //DA_PROJ2_NEARESTNEIGHBOR_H
