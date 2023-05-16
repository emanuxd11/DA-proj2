// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_VERTEX_EDGE
#define DA_TP_CLASSES_VERTEX_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

class Edge;

#define INF std::numeric_limits<int>::max()

/************************* Vertex  **************************/

class Vertex {
public:
    explicit Vertex(int id);

    bool operator<(Vertex &vertex) const; // // required by MutablePriorityQueue

    int getId() const;

    std::vector<Edge *> getAdj() const;

    bool isVisited() const;

    bool isProcessing() const;

    unsigned int getIndegree() const;

    int getDist() const;

    Edge *getPath() const;

    std::vector<Edge *> getIncoming() const;

    void setId(int info);

    void setVisited(bool visited);

    void setProcesssing(bool processing);

    void setIndegree(unsigned int indegree);

    void setDist(int dist);

    void setPath(Edge *path);

    Edge *addEdge(Vertex *dest, int w, int c);

    bool removeEdge(int destID);

    friend class MutablePriorityQueue<Vertex>;

    void setIndegreeUnavailable(int indegree_unavailable);

    int getIndegreeUnavailable() const;

protected:
    int id;                // identifier

    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    int indegree = -1; // used by topsort
    int indegree_unavailable = 0;
    int dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0;        // required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, int w, int c);

    Vertex *getDest() const;

    int getCapacity() const;

    int getCost() const;

    bool isSelected() const;

    Vertex *getOrig() const;

    Edge *getReverse() const;

    int getFlow() const;

    void setSelected(bool selected);

    void setReverse(Edge *reverse);

    void setFlow(int flow);

    void setCost(int c);

    bool isAlfaService() const;

    bool isStandardService() const;

    void setAvailable(bool available);

    bool getAvailable();
protected:
    Vertex *dest; // destination vertex

    int weight; // edge weight, can also be used for capacity
    int custo;
    bool available = true;

    int capacity; // edge capacity, can also be used for capacity
    int cost;


    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    int flow; // for flow-related problems
};

#endif /* DA_TP_CLASSES_VERTEX_EDGE */