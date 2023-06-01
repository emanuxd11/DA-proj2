//
// Created by catar on 01/06/2023.
//

#ifndef DA_PROJ2_TRIANGULARAPPROX_H
#define DA_PROJ2_TRIANGULARAPPROX_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "../includes/Graph.h"

class TriangularApprox {
public:
    TriangularApprox(Graph g);
    std::vector<int> triangularApproximationTSP(const std::vector<Vertex *>& nodes);

protected:
    Graph graph;
    int haversine();
    int findNearestNeighbor(const std::vector<Vertex *>& nodes, int currentNodeIndex);
};

#endif //DA_PROJ2_TRIANGULARAPPROX_H
