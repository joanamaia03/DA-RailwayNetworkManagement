#include "components.h"

// VERTEX //
Vertex::Vertex(string Name, string District, string Municipality, string Township, string Line) {
    name = Name;
    district = District;
    municipality = Municipality;
    township = Township;
    line = Line;
}

bool Vertex::operator<(Vertex a) {
    return price < a.price;
}

string Vertex::getName() {
    return name;
}

string Vertex::getDistrict() {
    return district;
}

string Vertex::getMunicipality() {
    return municipality;
}

string Vertex::getTownship() {
    return township;
}

string Vertex::getLine() {
    return line;
}

vector<Edge *> Vertex::getEdgesOut() {
    return edgesOut;
} 

vector<Edge *> Vertex::getEdgesIn() {
    return edgesIn;
} 

Edge *Vertex::getPath() {
    return path;
}

void Vertex::addEdgeOut(Edge *newEdge) {
    edgesOut.push_back(newEdge);
}

void Vertex::addEdgeIn(Edge *newEdge) {
    edgesIn.push_back(newEdge);
}

void Vertex::setPath(Edge *from) {
    path = from;
}

void Vertex::setVisited(bool a) {
    visited = a;
}

bool Vertex::getVisited() {
    return visited;
}

void Vertex::reset() {
    setPath(nullptr);
    setPrice(-1);
    setVisited(false);
}

Vertex *Edge::getStationA() {
    return stationA;
}

Vertex *Edge::getStationB() {
    return stationB;
}

int Vertex::getPrice() {
    return price;
}

void Vertex::setPrice(int cost) {
    price = cost;
}

// EDGE //
Edge::Edge(Vertex *StationA, Vertex *StationB, int Capacity, string Service) {
    stationA = StationA;
    stationB = StationB;
    capacity = Capacity;
    service = Service;
    occupied = 0;
}

int Edge::getCapacity() {
    return capacity;
}

void Edge::setReverse(Edge *pass) {
    reverse = pass;
}

Edge *Edge::getReverse() {
    return reverse;
}

string Edge::getService() {
    return service;
}

int Edge::getOccupiedFlow() {
    return occupied;
}

int Edge::getAvailableFlow() {
    return capacity - occupied;
}

bool Edge::isAvailable() {
    return available;
}

void Edge::setOccupied(int value) {
    occupied = value;
}

void Edge::setAvailable(bool value) {
    available = value;
}

void Edge::reset() {
    setOccupied(0);
}
