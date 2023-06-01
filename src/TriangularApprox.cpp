//
// Created by catar on 01/06/2023.
//

#include "../includes/TriangularApprox.h"
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

TriangularApprox::TriangularApprox(Graph g) : graph(g)  {}

static double haversine(double lat1, double lon1, double lat2, double lon2){
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

int TriangularApprox::findNearestNeighbor(const std::vector<Vertex *>& nodes, int currentNodeIndex) {
    int nearestNeighbor = -1;
    double minDistance = std::numeric_limits<double>::max();

    for (int i = 0; i < nodes.size(); ++i) {
        if (i != currentNodeIndex && !nodes[i]->isVisited()) {
            double distance = ::haversine(nodes[currentNodeIndex]->getLatitude(),nodes[currentNodeIndex]->getLongitude() , nodes[i]->getLatitude(),nodes[i]->getLongitude() );
            if (distance < minDistance) {
                minDistance = distance;
                nearestNeighbor = i;
            }
        }
    }

    return nearestNeighbor;
}

std::vector<int> TriangularApprox::triangularApproximationTSP(const std::vector<Vertex *>& nodes) {
    int numNodes = nodes.size();
    std::vector<int> tour;
    tour.reserve(numNodes);

    // Start with the first node as the current node
    int currentNodeIndex = 0;
    nodes[currentNodeIndex]->setVisited(true);
    tour.push_back(nodes[currentNodeIndex]->getId());

    while (tour.size() < numNodes) {
        int nearestNeighborIndex = findNearestNeighbor(nodes, currentNodeIndex);
        nodes[nearestNeighborIndex]->setVisited(true);
        tour.push_back(nodes[nearestNeighborIndex]->getId());
        currentNodeIndex = nearestNeighborIndex;
    }

    // Connect back to the starting node
    tour.push_back(nodes[0]->getId());

    return tour;
}