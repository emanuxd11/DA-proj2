#ifndef PROJETO2_DATABASE_H
#define PROJETO2_DATABASE_H

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <regex>

class Database {
public:
    static Graph toyLoadGraph(std::string file_name);

    static Graph mediumLoadGraph(std::string file_name);

    static Graph realLoadGraph(std::string graph_name);
};

#endif
