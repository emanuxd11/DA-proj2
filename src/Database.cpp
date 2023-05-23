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

Graph Database::toyLoadGraph(std::string file_name) {
    std::ifstream toy_network("../docs/Project2Graphs/Toy-Graphs/" + file_name);
    if (!toy_network.is_open()) {
        throw std::runtime_error(file_name + " file not found in toy graphs directory!");
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

Graph loadNodes(std::string graph_name) {
    std::ifstream real_nodes("../docs/Project2Graphs/Real-World-Graphs/" + graph_name + "/nodes.csv");
    if (!real_nodes.is_open()) {
        throw std::runtime_error(graph_name + " not found in real graphs directory!");
    }

    Graph g;
    std::string line, id_str, longitude_str, latitude_str;
    double longitude, latitude;
    int id;

    // throwaway first line 🗑
    getline(real_nodes, line);

    while (getline(real_nodes, line)) {
        std::stringstream ss(line);

        std::getline(ss, id_str, ',');
        std::getline(ss, longitude_str, ',');
        std::getline(ss, latitude_str, ',');

        id = std::stoi(id_str);
        longitude = std::stod(longitude_str);
        latitude = std::stod(latitude_str);

        g.addVertex(id, longitude, latitude);
    }

    g.sortVertexSet();
    return g;
}

Graph Database::realLoadGraph(std::string graph_name) {

    Graph g = loadNodes(graph_name);

    std::ifstream real_edges("../docs/Project2Graphs/Real-World-Graphs/" + graph_name + "/edges.csv");
    if (!real_edges.is_open()) {
        throw std::runtime_error(graph_name + " not found in real graphs directory!");
    }

    std::string line, orig_id_str, dest_id_str, dist_str;
    int orig_id, dest_id;
    float distance;

    // throw away first line 🗑
    getline(real_edges, line);

    while (getline(real_edges, line)) {
        std::stringstream ss(line);

        std::getline(ss, orig_id_str, ',');
        std::getline(ss, dest_id_str, ',');
        std::getline(ss, dist_str);

        orig_id = std::stoi(orig_id_str);
        dest_id = std::stoi(dest_id_str);
        distance = std::stof(dist_str);

        g.addBidirectionalEdge(orig_id, dest_id, distance);
    }

    return g;
}
