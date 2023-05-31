#include "../includes/NearestNeighbor.h"
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

NearestNeighbor::NearestNeighbor(Graph g) : graph(g)  {}

Edge *getNearestVertex(Vertex *v) {
    float distance = INF;
    Edge *nearest_vertex_path = nullptr;

    for (auto e : v->getAdj()) {
        if (e->getDest()->isVisited()) continue;

        if (e->getDistance() < distance) {
            distance = e->getDistance();
            nearest_vertex_path = e;
        }
        /* cout << "distance IS shorter" << endl;
    } else {
        cout << "distance not shorter" << endl;
    } */
    }

    return nearest_vertex_path;
}

bool NearestNeighbor::calculateTour(int idx) {
    graph.markAllUnvisited();

    Vertex *start = graph.getVertexSet()[idx];
    Vertex *current = start;

    start->setVisited(true);

    while (true) {
        Edge *path = getNearestVertex(current);
        if (path == nullptr) {
            break;
        }

        path->getDest()->setVisited(true);
        current->setPath(path);
        current = path->getDest();
    }

    bool found_final_edge = false;
    for (auto e : current->getAdj()) {
        if (e->getDest()->getId() == start->getId()) {
            found_final_edge = true;
            current->setPath(e);
        }
    }

    if (!found_final_edge) {
        cout << "Error, could not connect all edges!" << endl;
        return false;
    }

    stringstream ss;
    ss << start->getId() << " ";
    this->distance = start->getPath()->getDistance();
    for (auto now = start->getPath()->getDest(); now != start; ) {
        ss << now->getId() << " ";
        this->distance += now->getPath()->getDistance();
        now = now->getPath()->getDest();
    }
    ss << start->getId();
    this->order = ss.str();

    return true;
}

bool NearestNeighbor::run() {
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<std::size_t> distribution(0, graph.getVertexSet().size() - 1);

    long double min_distance = INF;
    string best_order;

    for (int i = 0; i < 50; i++) {
        size_t idx = distribution(rng);

        if (!calculateTour(idx)) {
            return false;
        }

        if (this->distance < min_distance) {
            best_order = this->order;
            min_distance = this->distance;
        }
    }

    this->order = best_order;
    this->distance = min_distance;

    cout << "Best Tour: " << this->order << endl;
    cout << "Total distance: " << fixed << setprecision(1) << this->distance << endl;

    return true;
}
