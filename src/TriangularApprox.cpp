

#include "../includes/TriangularApprox.h"
#include <string>
#include <random>

using namespace std;

TriangularApprox::TriangularApprox(Graph g) : graph(g)  {}

/**
 * PreOrder walk
 * It was supposed to iterate the mst in a preorder, to create the tour with the vertices of MST in preorder
 * @param u
 * @param tour
 * @param g
 * @return tour
 */
vector<int> TriangularApprox::preorderWalk(int u, vector<int> &tour, Graph& g){
    g.getVertexSet()[u]->setVisited(true);

    for (int v = 0; v < g.getNumVertex(); v++) {
        if (g.getVertexSet()[v]->hasEdge(u) && !(g.getVertexSet()[v]->isVisited())) {
            tour.push_back(g.getVertexSet()[v]->getId());
            preorderWalk(v, tour, g);
        }
    }

    return tour;
}

/**
 * Haversine Formula, calculates the distance between two vertices with their coordinates
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return distance between two vertices
 */
double TriangularApprox::haversine(double lat1, double lon1, double lat2, double lon2){

    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


/**
 * dfs to calculate the distances between all vertices with edges with haversine formula
 * @param v
 */
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


/**
 * Iterates trough the vertices of the graph and verifies if a specific vertice is in the MST and if it has a key value inferior to the
 * key value actual. If these conditions are met, updated the minimum value of key.
 * Purpose: to find the vertice with the smallest value key of the vertices not yet included in MST
 * @param key -> vector to find the edge with smallest distance
 * @param mst -> minimum spanning tree
 * @return
 */
int TriangularApprox::minKey(int key[], bool mst[]){
    int min = INT_MAX, min_index;

    for (int v = 0; v < graph.getNumVertex(); v++) {
        if (!mst[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}
/**
 * Implementation of prim algorithm to construct a MST (minimum spanning tree) which has the minimum value of distance of the edge
 * those vertices with the minimum value for the edges are added to the mst
 * @return graph g
 */
Graph TriangularApprox::prim(){
    Graph g;
    int key[graph.getNumVertex()];

    bool mst[graph.getNumVertex()];

    for (int i = 0; i < graph.getNumVertex(); i++) {
        key[i] = INT_MAX;
        mst[i] = false;
    }

    key[0] = 0;


    for (int i = 0; i < graph.getNumVertex() - 1; i++) {
        int u = minKey(key, mst);

        mst[u] = true;
        Vertex *a = graph.findVertex(u);
        g.addVertex(a->getId());
        for (int v = 0; v < graph.getNumVertex(); v++) {
            Vertex *b = graph.findVertex(v);
            if (a->getEdgeWeight(b->getId()) != 0 && !mst[v] && a->getEdgeWeight(b->getId()) < key[v]) {
                g.addEdge(a->getId(), b->getId(), a->getEdgeWeight(b->getId()));
                key[v] = a->getEdgeWeight(b->getId());
            }
        }
    }
    return g;

}


/**
 * Algorithm which calculates the result
 * 1st -> calculates distances of all vertices with their coordenates
 * 2st -> constructs the MST
 * 3st -> it was supposed to iterare the MST in preorder to create the vector tour with the vertices in the MST
 * @param nodes
 * @return tour, vector with the vertices of MST
 */
vector<int> TriangularApprox::triangularApproximationTSP(const vector<Vertex *>& nodes) {
    vector<int> tour;
    dfs(0);
    Graph g = prim();
    //tour = preorderWalk(0, tour, g);
    for(Vertex *v : g.getVertexSet()){
        tour.push_back(v->getId());
    }
    tour.push_back(0);

    return tour;
}
