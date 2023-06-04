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

void TriangularApprox::preorderWalk(int u, std::vector<bool> &visited, std::vector<int> &tour)
{
    visited[u] = true;
    tour.push_back(u);

    for (int v = 0; v < graph.getNumVertex(); v++) {
        if (graph.getVertexSet()[v]->hasEdge(u) && !visited[v])
            preorderWalk(v, visited, tour);
    }
}

double TriangularApprox::haversine(double lat1, double lon1, double lat2, double lon2){
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
//    int nearestNeighbor = -1;
//    double minDistance = std::numeric_limits<double>::max();
//
//    for (int i = 0; i < nodes.size(); ++i) {
//        if (i != currentNodeIndex && !nodes[i]->isVisited()) {
//            double distance = ::haversine(nodes[currentNodeIndex]->getLatitude(),nodes[currentNodeIndex]->getLongitude() , nodes[i]->getLatitude(),nodes[i]->getLongitude() );
//            if (distance < minDistance) {
//                minDistance = distance;
//                nearestNeighbor = i;
//            }
//        }
//    }
//
//    return nearestNeighbor;
}

std::vector<int> TriangularApprox::triangularApproximationTSP(const std::vector<Vertex *>& nodes) {
//    int numNodes = nodes.size();
    std::vector<int> tour;
//    tour.reserve(numNodes);
//
//    // Start with the first node as the current node
//    int currentNodeIndex = 0;
//    nodes[currentNodeIndex]->setVisited(true);
//    tour.push_back(nodes[currentNodeIndex]->getId());
//
//    while (tour.size() < numNodes) {
//        int nearestNeighborIndex = findNearestNeighbor(nodes, currentNodeIndex);
//        nodes[nearestNeighborIndex]->setVisited(true);
//        tour.push_back(nodes[nearestNeighborIndex]->getId());
//        currentNodeIndex = nearestNeighborIndex;
//    }
//
//    // Connect back to the starting node
//    tour.push_back(nodes[0]->getId());
//
//    std::vector<bool> visited(numNodes, false);
//    std::vector<int> preorderTour;
//    preorderTour.reserve(numNodes);
//    preorderWalk(0, visited, preorderTour);
//
//    return preorderTour;
    dfs(0);
    Graph g = prim();
//    for(Vertex *v : g.getVertexSet()){
//        cout << v->getId();
//    }

    return tour;
}

void TriangularApprox::dfs(int v){
    Vertex *s = graph.findVertex(v);
    s->setVisited(true);

    for(auto e : s->getAdj()){
        Vertex *t = e->getDest();
        if(!t->isVisited()){
            double distance = haversine(s->getLatitude(), s->getLongitude(), t->getLatitude(), t->getLongitude());
            e->setDistance(float(distance));
            dfs(t->getId());
        }
    }
}

void TriangularApprox::printMST(int parent[])
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < graph.getNumVertex(); i++) {
        Vertex *aux = graph.findVertex(i);
        Vertex *to = graph.findVertex(parent[i]);
        cout << parent[i] << " - " << i << " \t" << aux->getEdgeWeight(to->getId()) << " \n";
    }
}

int TriangularApprox::minKey(int key[], bool mstSet[]){
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph.getNumVertex(); v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

Graph TriangularApprox::prim(){
    Graph g;
    int key[graph.getNumVertex()];

    bool mstSet[graph.getNumVertex()];

    for (int i = 0; i < graph.getNumVertex(); i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;

//    g.addVertex(-1);

    for (int count = 0; count < graph.getNumVertex() - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = true;
        Vertex *a = graph.findVertex(u);
        g.addVertex(a->getId());
        for (int v = 0; v < graph.getNumVertex(); v++) {
            Vertex *b = graph.findVertex(v);
            if (a->getEdgeWeight(b->getId()) != 0 && !mstSet[v] && a->getEdgeWeight(b->getId()) < key[v]) {
                g.addEdge(a->getId(), b->getId(), a->getEdgeWeight(b->getId()));
                //parent[v] = u, key[v] = a->getEdgeWeight(b->getId());
            }
        }
    }
    return g;
    //printMST(parent);

}