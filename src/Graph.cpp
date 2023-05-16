// By: Gonçalo Leão

#include "../includes/Graph.h"
using namespace std;

// Pode ser útil mas mudar as classes
/* void Graph::setStationHash(std::unordered_map<int, Station> const &stations) {
    this->stationHash = stations;
}

void Graph::setInvertedHash(std::unordered_map<std::string, int> const &stationsInverse) {
    this->inverseHash = stationsInverse;
} */

/* std::unordered_map<int, Station> Graph::getStationHash() {
    return this->stationHash;
}

std::unordered_map<std::string, int> Graph::getInvertedHash() {
    return inverseHash;
}
*/

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

bool Graph::empty() {
    return vertexSet.empty();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex *Graph::findVertex(const int &id) const {
    /* if (stationHash.count(id) == 0) {
        return nullptr;
    } */

    for (auto v: vertexSet) {
        if (v->getId() == id) {
            return v;
        }
    }

    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(const int &id) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getId() == id)
            return i;
    return -1;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

bool Graph::deleteVertex(const int &id){
    for (auto it = vertexSet.begin(); it != vertexSet.end(); ++it) {
        if ((*it)->getId() == id) {
            vertexSet.erase(it);
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge capacity (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, int cap, int cost) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, cap, cost);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, int cap, int cost) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, cap, cost);
    auto e2 = v2->addEdge(v1, cap, cost);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

// Pode ser útil mas com classes diferentes
/*
std::unordered_set<std::string> Graph::getDistricts() {
    return districts;
}

std::unordered_set<std::string> Graph::getMunicipalities() {
    return municipalities;
}

void Graph::setDistricts(std::unordered_set<std::string> districts) {
    this->districts = districts;
}

void Graph::setMunicipalities(std::unordered_set<std::string> municipalities) {
    this->municipalities = municipalities;
}

int Graph::getStation(const std::string &name) {
    auto it = inverseHash.find(name);
    if (it == inverseHash.end()) {
        throw std::runtime_error("Invalid station name");
    }

    return it->second;
}

Station Graph::getStation(int id) {
    auto it = stationHash.find(id);
    if (it == stationHash.end()) {
        throw std::runtime_error("Invalid station id");
    }

    return it->second;
}
*/

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}


