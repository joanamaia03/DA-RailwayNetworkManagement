#ifndef COMP_H
#define COMP_H

#include <vector>
#include <string>
#include <bits/stdc++.h>
#include "MutablePriorityQueue.h"
using namespace std;

struct District;
struct Municipality {
    string name;
    District *district;
    int neededTrains;
};

struct District {
    string name;
    vector<Municipality *> municipalities;
};

class Edge;
class Vertex {
public:
    Vertex(string Name, string District, string Municipality, string Township, string Line);
    bool operator<(Vertex a);

    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();
    Edge *getPath();
    int getPrice();
    bool getVisited();

    vector<Edge *> getEdgesOut();
    vector<Edge *> getEdgesIn();
 
    void setPath(Edge *from);
    void addEdgeOut(Edge *newEdge);
    void addEdgeIn(Edge *newEdge);
    void setPrice(int cost);
    void setVisited(bool a);

    void reset();
    friend class MutablePriorityQueue<Vertex>;

protected:
    string name;
    string district;
    string municipality;
    string township;
    string line; 
    int price = -1;
    bool visited = false;

    Edge *path = nullptr;
    vector<Edge *> edgesOut;
    vector<Edge *> edgesIn;
    int queueIndex; // required by MPQ
};

class Edge {
public:
    Edge(Vertex *StationA, Vertex *StationB, int Capacity, string Service);
    
    string getService();
    Vertex *getStationA();
    Vertex *getStationB();
    Edge *getReverse();
    int getCapacity();
    int getOccupiedFlow();
    int getAvailableFlow();
    bool isAvailable();

    void setAvailable(bool value);
    void setReverse(Edge *pass);
    void setOccupied(int value);
    void reset();

protected:
    string service;
    Vertex *stationA;
    Vertex *stationB;
    Edge *reverse;
    int capacity;
    int occupied;
    bool available = true;
};

#endif
