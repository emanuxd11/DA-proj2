// By: Gonçalo Leão

#include "../includes/VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id) : id(id) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge capacity (w).
 */
Edge *Vertex::addEdge(Vertex *d, int w, int c) {
    auto newEdge = new Edge(this, d, w, c);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                } else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        } else {
            it++;
        }
    }
    return removedEdge;
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

int Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(int dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
    int hihi;
}

void Vertex::setIndegreeUnavailable(int indegree_unavailable) {
    this->indegree_unavailable = indegree_unavailable;
}

int Vertex::getIndegreeUnavailable() const {
    return indegree_unavailable;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, int w, int c) : orig(orig), dest(dest), capacity(w), cost(c) {}

Vertex *Edge::getDest() const {
    return this->dest;
}

int Edge::getCapacity() const {
    return this->capacity;
}

int Edge::getCost() const{
    return this->cost;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

int Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(int flow) {
    this->flow = flow;
}

void Edge::setCost(int c){
    this->cost = c;
}

bool Edge::isStandardService() const {
    return cost == 2;
}

bool Edge::isAlfaService() const {
    return custo == 4;
}

void Edge::setAvailable(bool available) {
    this->available = available;
}

bool Edge::getAvailable() {
    return available;
}
