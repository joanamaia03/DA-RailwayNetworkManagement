#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <queue>
#include "Components.h"

class Graph {
public:
    Graph();

    void reset();
    void resetPaths();
    void resetDeletions();
    bool districtExists(string name);
    bool vertexExists(string name);
    unordered_map<string, Vertex *> getVertexes();
    District *getDistrict(string name);
    Vertex *getVertex(string name);

    // Tasks
    std::vector<std::pair<string,string>> MaxFlowFullRail();
    int minCost(string StationA, string StationB);
    int maxTrains(string StationA, string StationB);
    vector<pair<std::string, int>> assignBudgets(int k,int x);
    vector<string> affectedStations( int k);
    int MaxFlowSpecificStat(string station);

private:
    bool bfs(string StationA, string StationB);
    unordered_map<string, Vertex *> vertexes;
    unordered_map<string, District *> districts;

    bool bfs_municipality(string municipality);
    bool bfs_district(string district);
};

#endif
