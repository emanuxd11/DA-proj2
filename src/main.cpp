#include <iostream>
#include "../includes/Graph.h"
#include "../includes/Database.h"
#include "../includes/Backtracking_TSP.h"

using namespace std;

const vector<string> extra_graphs = {
        "edges_25.csv",
        "edges_50.csv",
        "edges_75.csv",
        "edges_100.csv",
        "edges_200.csv",
        "edges_300.csv",
        "edges_400.csv",
        "edges_500.csv",
        "edges_600.csv",
        "edges_700.csv",
        "edges_800.csv",
        "edges_900.csv"
};

string getInput() {
    string input_string;
    std::getline(std::cin, input_string);
    return input_string;
}

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

bool nearestNeighbor(Graph g) {
    g.markAllUnvisited();

    Vertex *start = g.getVertexSet().front();
    Vertex *current = start;

    start->setVisited(true);

    while (true) {
        // cout << "Currently at vertex " << current->getId() << endl;

        Edge *path = getNearestVertex(current);
        if (path == nullptr) {
            break;
        }

        path->getDest()->setVisited(true);
        current->setPath(path);
        current = path->getDest();
    }

    // find edge that connects current to start
    bool found_final_edge = false;
    for (auto e : current->getAdj()) {
        if (e->getDest()->getId() == start->getId()) {
            cout << "Found edge that connects current to start!" << endl;
            found_final_edge = true;
            current->setPath(e);
        }
    }

    int not_visited = 0;
    for (auto v : g.getVertexSet()) {
        if (!v->isVisited()) {
            not_visited++;
        }
    }

    if (not_visited > 0) cout << "(not all vertices were visited)" << endl;
    else cout << "(all vertices were visited)" << endl;

    if (!found_final_edge) {
        cout << "Error, could not connect all edges!" << endl;

        return false;
    }

    long double total_distance = start->getPath()->getDistance();
    for (auto now = start->getPath()->getDest(); now != start; ) {
        total_distance += now->getPath()->getDistance();
        now = now->getPath()->getDest();
    }

    cout << "Total distance = " << (int)total_distance << endl;

    /* cout << "Current id = " << current->getId() << endl;
    cout << "Start id = " << start->getId() << endl; */

    return true;
}

void displayMenu() {
    static vector<string> options = {
            "1) Load toy dataset",
            "2) Load extra medium-sized dataset",
            "3) Load real dataset",
            "4) Backtracking Algorithm",
            "5) Nearest Neighbor Heuristic approximation (might not work for all graphs)",
            "0) Quit"
    };

    cout << " <-----------------> Menu <-----------------> " << endl;
    for (string const &option: options) {
        cout << option << endl;
    }
    cout << "Insert option: ";
}

int main() {
    Graph g;

    int opt = 1;
    while (opt) {
        displayMenu();
        cin >> opt;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opt == 1) {
            cout << "Please input toy graph file name: ";
            string file_name;
            cin >> file_name;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            g = Database::toyLoadGraph(file_name);

        } else if (opt == 2) {
            for (int i = 1; i <= extra_graphs.size(); i++) {
                cout << i << " - " << extra_graphs[i - 1] << endl;
            }
            cout << "Pick an option: ";
            int opt_number;
            cin >> opt_number;
            g = Database::mediumLoadGraph(extra_graphs[opt_number - 1]);

        } else if (opt == 3) {
            cout << "Please input real graph directory name (graph1/2/3): ";
            string graph_name;
            cin >> graph_name;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            g = Database::realLoadGraph(graph_name);

        } else if (opt == 4) {
            if (g.getVertexSet().empty()) {
                cout << "Please load a graph first!" << endl;
                continue;
            }

            BacktrackingAlgorithm tspSolver(g);
            std::vector<int> bestTour = tspSolver.solveBacktrackingAlgorithm();

            // Print the best tour
            if (bestTour.empty()) {
                std::cout << "No solution found!" << std::endl;
            } else {
                std::cout << "Best Tour: ";
                for (int vertex : bestTour) {
                    std::cout << vertex << " ";
                }
                std::cout << bestTour[0] << " ";
                std::cout << std::endl;
                std::cout << "Total distance: " << tspSolver.getBestTourCost() << std::endl;
            }

        } else if (opt == 5) {
            if (g.getVertexSet().empty()) {
                cout << "Please load a graph first!" << endl;
                continue;
            }

            nearestNeighbor(g);
            
        } else if (opt == 9) {
            break;
        }
    }

    return 0;
}
