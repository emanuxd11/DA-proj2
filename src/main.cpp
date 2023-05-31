#include <iostream>
#include "../includes/Graph.h"
#include "../includes/Database.h"
#include "../includes/Backtracking_TSP.h"
#include "../includes/NearestNeighbor.h"

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

void displayMenu() {
    static vector<string> options = {
            "1) Load toy dataset",
            "2) Load extra medium-sized dataset of fully connected graphs",
            "3) Load real dataset",
            "4) Backtracking Algorithm",
            "5) Nearest Neighbor Heuristic approximation (for fully connected graphs)",
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

            NearestNeighbor NN(g);
            NN.run();
            
        } else if (opt == 9) {
            break;
        }
    }

    return 0;
}
