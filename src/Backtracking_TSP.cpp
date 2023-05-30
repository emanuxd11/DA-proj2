#include "../includes/Backtracking_TSP.h"

BacktrackingAlgorithm::BacktrackingAlgorithm(Graph& graph) : graph(graph), bestTourCost(std::numeric_limits<int>::max()) {}

std::vector<int> BacktrackingAlgorithm::solveBacktrackingAlgorithm() {
    int numVertices = graph.getNumVertex();
    std::vector<bool> visited(numVertices, false);
    std::vector<int> currentTour;
    std::vector<int> bestTour;
    float totalCost = 0.0;
    float minCost = std::numeric_limits<int>::max();

    // Find the starting vertex labeled with zero-identifier
    Vertex* startVertex = graph.findVertex(0);
    if (startVertex == nullptr) {
        std::cout << "Starting vertex not found!" << std::endl;
        return bestTour; // Return an empty tour
    }

    // Call the backtracking function
    backtrackingTSP(startVertex, visited, currentTour, bestTour, totalCost, minCost);

    return bestTour;
}

float BacktrackingAlgorithm::getBestTourCost() const {
    return bestTourCost;
}

void BacktrackingAlgorithm::backtrackingTSP(Vertex* currentVertex, std::vector<bool>& visited,
                                std::vector<int>& currentTour, std::vector<int>& bestTour,
                                float totalCost, float& minCost) {
    visited[currentVertex->getId()] = true;
    currentTour.push_back(currentVertex->getId());

    // Base case: All vertices visited, check if the current vertex has an edge to the starting vertex
    if (currentTour.size() == graph.getNumVertex() && currentVertex->hasEdge(0)) {
        float tourCost = totalCost + currentVertex->getEdgeWeight(0);
        if (tourCost < minCost) {
            minCost = tourCost;
            bestTour = currentTour;
            bestTourCost = minCost;
        }
    } else {
        // Recursive case: Visit unvisited neighbors
        for (Edge* edge : currentVertex->getAdj()) {
            Vertex* neighbor = edge->getDest();
            if (!visited[neighbor->getId()]) {
                float edgeCost = edge->getDistance();
                totalCost += edgeCost;
                backtrackingTSP(neighbor, visited, currentTour, bestTour, totalCost, minCost);
                totalCost -= edgeCost; // Backtrack
            }
        }
    }

    // Mark the current vertex as unvisited and remove it from the current tour
    visited[currentVertex->getId()] = false;
    currentTour.pop_back();
}
