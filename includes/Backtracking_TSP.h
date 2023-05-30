#ifndef BACKTRACKING_ALGORITHM
#define BACKTRACKING_ALGORITHM

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "../includes/Graph.h"

class BacktrackingAlgorithm {
public:
    BacktrackingAlgorithm(Graph& graph);

    std::vector<int> solveBacktrackingAlgorithm();
    float getBestTourCost() const;

private:
    Graph& graph;
    float bestTourCost;

    void backtrackingTSP(Vertex* currentVertex, std::vector<bool>& visited,
                         std::vector<int>& currentTour, std::vector<int>& bestTour,
                         float totalCost, float& minCost);
};

#endif /* BACKTRACKING_ALGORITHM */