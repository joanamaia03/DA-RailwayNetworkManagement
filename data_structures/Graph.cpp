#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "graph.h"
#include "MutablePriorityQueue.h"


using namespace std;

Graph::Graph() {
    ifstream file;
    string line, a, b, c, d, e;
    file.open("../data/stations.csv");  

    unordered_set<string> muns;  

    getline(file, line);
    while (getline(file, line)) {
        stringstream thisLine(line);

        getline(thisLine, a, ','); // Name
        getline(thisLine, b, ','); // District
        getline(thisLine, c, ','); // Municipality
        getline(thisLine, d, ','); // Township
        getline(thisLine, e, '\n'); // Line
        
        Vertex *newVertex = new Vertex(a, b, c, d, e);
        vertexes[newVertex->getName()] = newVertex;

        if (districts.find(b) == districts.end()) {
            District *newDistrict = new District();
            newDistrict->name = b;
            districts[b] = newDistrict;
        }

        if (muns.find(b + "_" + c) == muns.end()) {
            Municipality *newMunicipality = new Municipality();
            newMunicipality->name = c;
            newMunicipality->district = districts[b];
            muns.insert(b + "_" + c);
            districts[b]->municipalities.push_back(newMunicipality); // BAD_ALLOC????
        }
    }
    file.close();
    file.open("../data/network.csv");

    getline(file, line);
    while (getline(file, line)) {
        stringstream thisLine(line);

        getline(thisLine, a, ','); // Station_A
        getline(thisLine, b, ','); // Station_B
        getline(thisLine, c, ','); // Capacity
        getline(thisLine, d, '\n'); // Service

        Edge *newEdge = new Edge(vertexes[a], vertexes[b], stoi(c), d);
        Edge *newEdgee = new Edge(vertexes[b], vertexes[a], stoi(c), d);
        newEdge->setReverse(newEdgee);
        newEdgee->setReverse(newEdge);
        vertexes[a]->addEdgeOut(newEdge);
        vertexes[a]->addEdgeIn(newEdgee);
        vertexes[b]->addEdgeOut(newEdgee);
        vertexes[b]->addEdgeOut(newEdge);
    }
    cout << vertexes.size() << '\n';

    file.close();
    muns.clear();
};

void Graph::reset() {
    for (unordered_map<string, Vertex *>::iterator it = vertexes.begin(); it != vertexes.end(); it++) {
        it->second->reset();
        for (int i = 0; i < it->second->getEdgesOut().size(); i++) {
            it->second->getEdgesOut()[i]->reset();
        }
    }
}

void Graph::resetDeletions(){
    for (unordered_map<string, Vertex *>::iterator it = vertexes.begin(); it != vertexes.end(); it++){
        for (int i = 0; i < it->second->getEdgesOut().size(); i++){
            it->second->getEdgesOut()[i]->setAvailable(true);
        }
    }
}

void Graph::resetPaths() {
    for (unordered_map<string, Vertex *>::iterator it = vertexes.begin(); it != vertexes.end(); it++)
        it->second->setPath(nullptr);
}

District *Graph::getDistrict(string name) {
    return districts[name];
}

unordered_map<string, Vertex *> Graph::getVertexes() {
    return vertexes;
}

Vertex *Graph::getVertex(string name) {
    if (vertexExists(name)) return vertexes[name];
    return nullptr;
}

bool Graph::vertexExists(string name) {
    return vertexes.find(name) != vertexes.end();
}

bool Graph::districtExists(string name) {
    return districts.find(name) != districts.end();
}

bool Graph::bfs(string StationA, string StationB) {
    resetPaths();
    queue<Vertex *> q;
    q.push(vertexes[StationA]);

    while (!q.empty()) {
        Vertex *current = q.front();
        q.pop();

        if (current->getName() == StationB) return true;
        for (Edge *edge : current->getEdgesOut()) { 
            Vertex *next = edge->getStationB();
            if (next->getPath() != nullptr || next->getName() == StationA || !edge->isAvailable()) continue;
            if (edge->getOccupiedFlow() >= edge->getCapacity()) continue;
            q.push(next);
            next->setPath(edge);
        }

        for (Edge *edge : current->getEdgesIn()) { 
            Vertex *next = edge->getStationA();
            if (next->getPath() != nullptr || next->getName() == StationA || !edge->isAvailable()) continue;
            if (edge->getOccupiedFlow() <= 0) continue;
            q.push(next);
            next->setPath(edge);
        }
    }    

    return false;
}

bool Graph::bfs_district(string district){
    resetPaths();
    queue<Vertex *> q;
    q.push(vertexes[district]);
    int comboios=0;
    unordered_map<string, int> districtData;
    while (!q.empty()) {
        Vertex *current = q.front();
        q.pop();

        if (current->getDistrict() != district) continue;
        for (Edge *edge : current->getEdgesOut()) {
            Vertex *next = edge->getStationB();
            if (edge->getOccupiedFlow() < edge->getCapacity()) {
                q.push(next);
                next->setPath(edge);
                comboios+=edge->getCapacity()-edge->getOccupiedFlow();
                if(districtData.find(next->getDistrict())==districtData.end()){
                    districtData[next->getDistrict()]=edge->getCapacity()-edge->getOccupiedFlow();
                }
                else{
                    districtData[next->getDistrict()]+=edge->getCapacity()-edge->getOccupiedFlow();
                }
            }
        }
    }

    return false;
}

bool Graph::bfs_municipality(string municipality) {
    resetPaths();
    queue<Vertex *> q;
    q.push(vertexes[municipality]);
    int comboios=0;
    unordered_map<string, int> municipalityData;
    while (!q.empty()) {
        Vertex *current = q.front();
        q.pop();

        if (current->getMunicipality() != municipality) continue;
        for (Edge *edge : current->getEdgesOut()) {
            Vertex *next = edge->getStationB();
            if (edge->getOccupiedFlow() < edge->getCapacity()) {
                q.push(next);
                next->setPath(edge);
                comboios+=edge->getCapacity()-edge->getOccupiedFlow();
                if(municipalityData.find(next->getMunicipality())==municipalityData.end()){
                    municipalityData[next->getMunicipality()]=edge->getCapacity()-edge->getOccupiedFlow();
                }
                else{
                    municipalityData[next->getMunicipality()]+=edge->getCapacity()-edge->getOccupiedFlow();
                }
            }
        }
    }

    return false;
}

int Graph::maxTrains(string StationA, string StationB) {
    int maxFlow = 0;

    while (bfs(StationA, StationB)) {
        int maxi = INT_MAX;
        Vertex *current = vertexes[StationB];

        while (current->getName() != StationA) {
            if (current->getPath()->getStationA() == current) {
                maxi = min(maxi, current->getPath()->getOccupiedFlow());
                current = current->getPath()->getStationB();
                continue;
            }
            maxi = min(maxi, current->getPath()->getAvailableFlow());
            current = current->getPath()->getStationA();
        }
        
        maxFlow += maxi;
        current = vertexes[StationB];
        while (current->getName() != StationA) {
            if (current->getPath()->getStationA() == current) {
                current->getPath()->setOccupied(current->getPath()->getOccupiedFlow() - maxi);
                current = current->getPath()->getStationB();
                continue;
            } 

            current->getPath()->setOccupied(current->getPath()->getOccupiedFlow() + maxi);
            current = current->getPath()->getStationA();
        }
    }

    return maxFlow;
}

int Graph::minCost(string StationA, string StationB) {
    MutablePriorityQueue<Vertex> q;

    for (auto it : vertexes) {
        it.second->setPrice(INT_MAX);
    }

    Vertex *current = vertexes[StationA];
    current->setPrice(0);
    q.insert(current);

    while (!q.empty()) {
        current = q.extractMin();
        if (current->getVisited()) continue;
        current->setVisited(true);
        if (current->getName() == StationB) break;

        for (Edge *edge : current->getEdgesOut()) {
            int cost = edge->getCapacity() * 2;
            if (edge->getService() != "STANDARD") cost *= 2;
            if ((cost + current->getPrice() > edge->getStationB()->getPrice()) || edge->getStationB()->getVisited()) continue;

            edge->getStationB()->setPath(edge);
            edge->getStationB()->setPrice(cost + current->getPrice());
            q.insert(edge->getStationB());
        }
    }

    int a = INT_MAX;
    current = vertexes[StationB];
    while (current != vertexes[StationA]) {
        a = min(current->getPath()->getCapacity(), a);
        current = current->getPath()->getStationA();
    }

    return a;
}

vector<pair<string, int>> Graph::assignBudgets(int k, int x){
    vector<pair<string, int>> dist_munData;
    for(auto i=vertexes.begin();i!=vertexes.end();i++){
        if(x==1){
            int comboios=bfs_district(i->second->getDistrict());
            dist_munData.push_back(make_pair(i->second->getName(),comboios));
        }
        if(x==2){
            int comboios=bfs_municipality(i->second->getMunicipality());
            dist_munData.push_back(make_pair(i->second->getName(),comboios));
        }
    }
    sort(dist_munData.begin(),dist_munData.end());
    return dist_munData;
}

int Graph::MaxFlowSpecificStat(string station){
    int n = 0;
    for (unordered_map<string, Vertex *>::iterator j = vertexes.begin(); j != vertexes.end(); j++){
        if (station != j->second->getName()) {
            int cur = maxTrains(station, j->second->getName());
            if (cur > n) {
                n = cur;
            }
            reset();
        }
    }
    return n;
}

vector<string> Graph::affectedStations( int k){
    unordered_map<Vertex*,int> flowRestricted;
    vector<pair<Vertex*,int>> ordem;
    for(auto i: vertexes){
        flowRestricted[i.second]= MaxFlowSpecificStat(i.first);
    }
    resetDeletions();
    for(auto i: vertexes){
       ordem.push_back({i.second, MaxFlowSpecificStat(i.first)-flowRestricted[i.second]});
    }
    sort(ordem.begin(),ordem.end(),[](const pair<Vertex*,int> &l, const pair<Vertex*,int> &r){return l.second>r.second;});
    vector<string> result;
    if(k>ordem.size()) k=ordem.size();
    for(int i=0;i<k;i++){
        result.push_back(ordem[i].first->getName());
    }
    return result;
}

std::vector<std::pair<string,string>> Graph::MaxFlowFullRail(){
    int n = 0;
    int count = 0;
    cout <<"      0%                                                 100%\n" << "Loading";
    std::vector<std::pair<string,string>> max;
    for(unordered_map<string, Vertex *>::iterator i = vertexes.begin(); i != vertexes.end(); i++){
        count ++;
        if (count%10 == 0){
            cout << "|";
        }
        for (unordered_map<string, Vertex *>::iterator j = vertexes.begin(); j != vertexes.end(); j++){
            if (i != j) {
                int cur = maxTrains(i->second->getName(), j->second->getName());
                if (cur > n) {
                    n = cur;
                    max.clear();
                    //cout << i->second->getName() << " --> ";
                    //cout << j->second->getName() << " " << cur << "\n";
                    string a = i->second->getName();
                    string b = j->second->getName();
                    max.push_back({a, b});
                }
                else if (cur == n) {
                    //cout << i->second->getName() << " --> ";
                    //cout << j->second->getName() << " " << cur << "\n";
                    string a = i->second->getName();
                    string b = j->second->getName();
                    max.push_back({a, b});
                }
                reset();
            }
        }
    }
    cout << "\n Finished \n";
    cout << "Max_Flow: " << n << '\n';
    cout << "the route that requires the most amount of trains is between Stations" << '\n';
    for (int i = 0 ; i < max.size(); i++) {
        cout << max[i].first << "-->" << max[i].second << '\n';
    }

    return max;
}
