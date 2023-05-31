#include "../includes/NearestNeighbor.h"
#include <sstream>
#include <string>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

NearestNeighbor::NearestNeighbor(Graph g) : graph(g)  {}

/**
 * This algorithm finds the nearest unvisited vertex to the one passed as argument.
 * Time complexity: O(|V|).
 * @param v Vertex, vertex in question.
 * @return nearest_vertex_path, Edge*, or nullptr in case no unvisited vertex is found in v's adjacency list.
 */
Edge *getNearestVertex(Vertex *v) {
    float distance = INF;
    Edge *nearest_vertex_path = nullptr;

    for (auto e : v->getAdj()) {
        if (e->getDest()->isVisited()) continue;

        if (e->getDistance() < distance) {
            distance = e->getDistance();
            nearest_vertex_path = e;
        }
    }

    return nearest_vertex_path;
}

/**
 * This heuristic approximates a shortest hamiltonian cycle for a strongly connected graph (nearest neighbor heuristic).
 * It starts at a random vertex and always follows the path of least distance until all vertices are visited, then
 * linking back to the original vertex.
 * Time complexity: O(|V| * (|V| - 1)).
 * @param idx int, index for the random vertex in the vertex set.
 * @return true/false, bool, to indicate whether this heuristic is applicable or not (only works for
 * strongly connected graphs).
 */
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

/**
 * This function performs the complete heuristic. In this case we run it 50 times (50 is a good balance between
 * execution time and accuracy especially for the larger graphs that were provided), with 50 different random
 * starting vertices, and then simply take the best tour out of all 50.
 * Time complexity: O(|V| * (|V| - 1)).
 * @return true/false, bool, to indicate whether this heuristic is applicable or not (only works for
 * strongly connected graphs).
 */
bool NearestNeighbor::run() {
    std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<std::size_t> distribution(0, graph.getVertexSet().size() - 1);

    long double min_distance = INF;
    string best_order;

    for (int i = 0; i < 50; i++) {
        size_t idx = distribution(rng);

        calculateTour(idx);

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
