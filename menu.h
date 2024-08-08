
#ifndef DA_PROJECT_MENU_H
#define DA_PROJECT_MENU_H

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include "data_structures/Graph.h"
using namespace std;

class menu {
public:
    menu();

    // DISPLAYS
    void menuDisplay();
    void minTrainDisplay();

    // INPUT
    int readInteger(string prompt);
    string readString(string prompt);
    Vertex *readVertex(string prompt);
    Edge *readEdge(string prompt);

    // STATES 
    void mainMenu();
    void minTrainMenu();
    
private:
    Graph graph;
};


#endif //DA_PROJECT_MENU_H
