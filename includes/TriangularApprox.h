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
    int findNearestNeighbor(const std::vector<Vertex *>& nodes, int currentNodeIndex);
    void preorderWalk(int u, std::vector<bool> &visited, std::vector<int> &tour);
    void dfs(int v);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    int minKey(int key[], bool mstSet[]);
    Graph prim();
    void printMST(int parent[]);
};

#endif //DA_PROJ2_TRIANGULARAPPROX_H
