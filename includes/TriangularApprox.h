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

using namespace std;

class TriangularApprox {
public:
    TriangularApprox(Graph g);
    vector<int> triangularApproximationTSP(const vector<Vertex *>& nodes);

protected:
    Graph graph;
    vector<int> preorderWalk(int u, vector<int> &tour, Graph& g);
    void dfs(int v);
    double haversine(double lat1, double lon1, double lat2, double lon2);
    int minKey(int key[], bool mstSet[]);
    Graph prim();
};

#endif //DA_PROJ2_TRIANGULARAPPROX_H
