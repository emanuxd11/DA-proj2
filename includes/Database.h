//
// Created by manu on 3/15/23.
//

#ifndef PROJETO1_DATABASE_H
#define PROJETO1_DATABASE_H

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <regex>

class Database {
public:
    static Graph loadGraph();

    static std::unordered_map<int, int> loadNodes(std::unordered_set<std::string> &districts, std::unordered_set<std::string> &municipalities);

    static Graph loadGraph(std::vector<std::pair<std::string, std::string>> exclude);

    static std::unordered_map<std::string, int> invertedHash(std::unordered_map<int, int> stationHash);
private:

};


#endif //PROJETO1_DATABASE_H
