cmake_minimum_required(VERSION 3.22)
project(DA_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA_Project main.cpp menu.cpp menu.h data_structures/Graph.cpp data_structures/Graph.h data_structures/MutablePriorityQueue.h data_structures/Components.cpp data_structures/Components.h )