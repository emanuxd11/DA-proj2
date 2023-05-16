//
// Created by manu on 3/15/23.
//

#include "../includes/Database.h"

// métodos auxiliares
std::vector<std::string> lineParser(std::string const &line) {
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

// fim dos métodos auxiliares

std::unordered_map<std::string, int> Database::invertedHash(std::unordered_map<int, int/* uma classe nova ? */> stationHash) {
    std::unordered_map<std::string, int> inverse;
    for (auto &it: stationHash) {
        // inverse[it.second.getName()] = it.first;
    }

    return inverse;
}

std::unordered_map<int, int /* uma classe nova? */> Database::loadNodes(
        std::unordered_set<std::string> &districts,
        std::unordered_set<std::string> &municipalities) {

    std::unordered_map<int, int /* uma classe nova? */> stationHash;
    std::ifstream stations("../docs/stations.csv");

    if (stations.is_open()) {
        int count = 0;
        // Station station;
        std::string line;
        getline(stations, line); // throwaway first line read

        while (getline(stations, line)) {
            std::vector<std::string> fields = lineParser(line);

            /*
            station.setName(fields[0]);
            station.setDistrict(fields[1]);
            station.setMunicipality(fields[2]);
            station.setTownship(fields[3]);
            station.setLine(fields[4]);
            */

            if (!fields[1].empty()) {
                districts.insert(fields[1]);
            }
            if (!fields[2].empty()) {
                municipalities.insert(fields[2]);
            }

            // stationHash[count] = station;
            count++;
        }
    } else throw std::runtime_error("stations.csv file not found in docs directory!");

    return stationHash;
}

Graph Database::loadGraph() {
    std::ifstream network("../docs/network.csv");
    if (!network.is_open()) {
        throw std::runtime_error("network.csv file not found in docs directory!");
    }

    Graph g;
    std::unordered_set<std::string> districts, municipalities;
    std::unordered_map<int, int /* uma classe nova? */> stationHash = loadNodes(districts, municipalities);
    // g.setDistricts(districts);
    // g.setMunicipalities(municipalities);
    std::unordered_map<std::string, int> inverseStations = invertedHash(stationHash);

    std::string line, origStation, destStation;
    int origId, destId, custo, capacity;

    getline(network, line); // throwaway first line read
    while (getline(network, line)) {
        std::stringstream ss(line);
        std::vector<std::string> fields = lineParser(line);

        /* origStation = fields[0];
        destStation = fields[1];

        origId = inverseStations[origStation];
        destId = inverseStations[destStation];

        g.addVertex(origId);
        g.addVertex(destId);
        g.addBidirectionalEdge(origId, destId, capacity, custo); */
    }

    /* g.setStationHash(stationHash);
    g.setInvertedHash(inverseStations); */

    return g;
}

Graph Database::loadGraph(std::vector<std::pair<std::string, std::string>> exclude) {
    std::ifstream network("../docs/network.csv");
    if (!network.is_open()) {
        throw std::runtime_error("network.csv file not found in docs directory!");
    }

    Graph g;
    std::unordered_set<std::string> districts, municipalities;
    // auto stationHash = loadNodes(districts, municipalities);
    /* g.setDistricts(districts);
    g.setMunicipalities(municipalities); */
    // auto inverseStations = invertedHash(stationHash);

    std::string line, origStation, destStation;
    int origId, destId, custo, capacity;

    getline(network, line); // throwaway first line read
    while (getline(network, line)) {
        std::stringstream ss(line);
        std::vector<std::string> fields = lineParser(line);

        origStation = fields[0];
        destStation = fields[1];

        /*
        origId = inverseStations[origStation];
        destId = inverseStations[destStation];
         */

        g.addVertex(origId);
        g.addVertex(destId);

        bool skip = false;
        for (auto pair : exclude) {
            if ( (pair.first == origStation and pair.second == destStation)
                 or (pair.first == destStation and pair.second == origStation) ) {
                skip = true;
                break;
            }
        }

        if (!skip) {
            g.addBidirectionalEdge(origId, destId, capacity, custo);
        }
    }

    /* g.setStationHash(stationHash);
    g.setInvertedHash(inverseStations); */

    return g;
}