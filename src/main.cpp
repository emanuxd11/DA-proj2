#include <iostream>
#include <iomanip>
#include "../includes/Graph.h"
#include "../includes/Database.h"

using namespace std;

string getInput() {
    string input_string;
    std::getline(std::cin, input_string);
    return input_string;
}

void displayMenu() {
    static vector<string> options = {
            "1) Load toy dataset",
            "2) Load real dataset",
            "3) coming soon...3",
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

            // just for checking
            /* for (auto v : g.getVertexSet()) {
                if (g.isLabeled()) {
                    cout << "For vertex " << v->getId() << " in " << v->getLabel() << endl;
                } else {
                    cout << "For vertex " << v->getId() << ":" << endl;
                }

                for (auto adj : v->getAdj()) {
                    if (g.isLabeled()) {
                        cout << adj->getDistance() << "km away from " << adj->getDest()->getId() << " in " << adj->getDest()->getLabel() << endl;
                    } else {
                        cout << adj->getDistance() << "km away from " << adj->getDest()->getId() << endl;
                    }
                }
            } */

        } else if (opt == 2) {
            cout << "Please input real graph directory name (graph1/2/3): ";
            string graph_name;
            cin >> graph_name;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            g = Database::realLoadGraph(graph_name);

            // just for checking
            /* cout << setprecision(15);
            for (auto v : g.getVertexSet()) {
                cout << "For vertex " << v->getId() << " at (" << v->getLongitude() << ", " << v->getLatitude() << "):" << endl;
                for (auto adj : v->getAdj()) {
                    cout << adj->getDistance() << "km away from " << adj->getDest()->getId() << " at (" << adj->getDest()->getLongitude() << ", " << adj->getDest()->getLatitude() << "):"<< endl;
                }
            } */

        } else if (opt == 3) {
        } else if (opt == 9) {
            break;
        }
    }

    return 0;
}
