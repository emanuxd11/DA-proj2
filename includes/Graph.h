#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"
#include <unordered_map>
#include <unordered_set>

#include "VertexEdge.h"

class Graph {
public:
    ~Graph();

    Vertex *findVertex(const int &id) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const int &id);

    bool addVertex(const int &id, const double &longitude, const double &latitude);

    bool deleteVertex(const int &id);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge capacity (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, const float &distance);

    bool addBidirectionalEdge(const int &sourc, const int &dest, const float &distance);

    int getNumVertex() const;

    void sortVertexSet();

    std::vector<Vertex *> getVertexSet() const;

    bool empty();

    void setLabeled(bool has_label);

    bool isLabeled();

    void markAllUnvisited();

protected:
    std::vector<Vertex *> vertexSet;    // vertex set

    /*
     * Vector of only unvisited vertices.
     * This speeds up the final part of the
     * process of looking for the nearest vertex
     * in the Nearest Neighbor Heuristic.
     */
    std::vector<Vertex *> unvisited_vertices;

    bool has_labels = false;

    int **distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const int &id) const;

    bool findAugmentingPath(Vertex *s, Vertex *t);
};

void deleteMatrix(int **m, int n);

void deleteMatrix(int **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */