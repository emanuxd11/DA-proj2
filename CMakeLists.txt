cmake_minimum_required(VERSION 3.17)
project(DA_proj2)

set(CMAKE_CXX_STANDARD 17)

add_executable (
        DA_proj2 src/main.cpp
        src/Graph.cpp includes/Graph.h
        src/Heap.cpp includes/Heap.h
        src/UFDS.cpp includes/UFDS.h
        src/VertexEdge.cpp includes/VertexEdge.h
        src/Database.cpp includes/Database.h
        src/Backtracking_TSP.cpp)
