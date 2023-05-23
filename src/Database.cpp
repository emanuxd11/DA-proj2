#include "../includes/Database.h"

std::vector<std::string> toyParseLine(std::string const &line) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    bool in_quotes = false;

    while (std::getline(ss, field, ',')) {
        if (field.empty()) {
            fields.push_back(field);
            continue;
        }
        if (!in_quotes) {
            if (field.front() == '"' && field.back() != '"') {
                field.erase(0, 1);
                in_quotes = true;
            } else if (field.front() == '"' && field.back() == '"') {
                field = field.substr(1, field.size() - 2);
            }
            fields.push_back(field);
        } else {
            fields.back() += "," + field;
            if (field.back() == '"') {
                in_quotes = false;
                fields.back().pop_back();
            }
        }
    }

    return fields;
}

// implementations

void loadNodes(std::string file_path) {

    std::ifstream stations("../docs/stations.csv");

    if (stations.is_open()) {
        int count = 0;
        // Station station;
        std::string line;
        getline(stations, line); // throwaway first line read

        while (getline(stations, line)) {

        }
    } else throw std::runtime_error("stations.csv file not found in docs directory!");

    return ;
}

Graph Database::toyLoadGraph(std::string file_name) {
    std::cout << "before adding vertex";


    std::ifstream toy_network("../docs/Project2Graphs/Toy-Graphs/" + file_name);
    if (!toy_network.is_open()) {
        throw std::runtime_error(file_name + " file not found in docs directory!");
    }

    Graph g;
    std::string line, distance_str, orig_label, dest_label, orig_id_str, dest_id_str;
    int orig_id, dest_id;
    float distance = 0;

    getline(toy_network, line); // first line read
    bool has_label = (line.find("label") != std::string::npos);

    while (getline(toy_network, line)) {
        std::stringstream ss(line);

        std::getline(ss, orig_id_str, ',');
        std::getline(ss, dest_id_str, ',');
        if (has_label) {
            std::getline(ss, distance_str, ',');
            std::getline(ss, orig_label, ',');
            std::getline(ss, dest_label);
            g.setLabeled(true);
        } else {
            std::getline(ss, distance_str);
        }

        orig_id = std::stoi(orig_id_str);
        dest_id = std::stoi(dest_id_str);
        distance = std::stof(distance_str);

        g.addVertex(orig_id);
        g.addVertex(dest_id);

        // set labels if necessary
        if (has_label) {
            g.findVertex(orig_id)->setLabel(orig_label);
            g.findVertex(dest_id)->setLabel(dest_label);
        }

        g.addBidirectionalEdge(orig_id, dest_id, distance);
    }

    g.sortVertexSet();
    return g;
}