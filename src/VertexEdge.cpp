// By: Gonçalo Leão

#include <utility>

#include "../includes/VertexEdge.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id) : id(id) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge capacity (w).
 */
Edge *Vertex::addEdge(Vertex *d, float distance) {
    auto newEdge = new Edge(this, d, distance);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

bool Vertex::hasEdge(int destID) const {
    for (Edge* edge : adj) {
        if (edge->getDest()->getId() == destID) {
            return true;
        }
    }
    return false;
}

double Vertex::getEdgeWeight(int destID) const {
    for (Edge* edge : adj) {
        if (edge->getDest()->getId() == destID) {
            return edge->getDistance();
        }
    }
    return std::numeric_limits<double>::infinity(); // Return infinity if there is no edge to the destination vertex
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

// for real world graphs
double Vertex::getLongitude() {
    return this->longitude;
}

double Vertex::getLatitude() {
    return this->latitude;
}

void Vertex::setLongitude(double longitude) {
    this->longitude = longitude;
}

void Vertex::setLatitude(double latitude) {
    this->latitude = latitude;
}

// for toy graphs
std::string Vertex::getLabel() {
    return this->label;
}

void Vertex::setLabel(std::string label) {
    this->label = std::move(label);
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, float distance) : orig(orig), dest(dest), distance(distance) {}

Vertex *Edge::getDest() const {
    return this->dest;
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

void Edge::setAvailable(bool available) {
    this->available = available;
}

bool Edge::getAvailable() {
    return available;
}

float Edge::getDistance() const {
    return distance;
}

void Edge::setDistance(float distance) {
    this->distance = distance;
}

