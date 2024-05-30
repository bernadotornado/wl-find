#include "graph.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <climits>
#include <algorithm>

Map::Map()
{
    // Initialize the map
    this->stations = std::vector<Station*>();
    this->lines = std::vector<Line*>();
}

void Map::PrintMap(){
    for (auto station: this->stations){
        station->PrintStation();
    }
    for (auto line: this->lines){
        line->PrintLine();
    }
}
void Map::AddLine(Line *line)
{
    // Add a line to the map
    this->lines.push_back(line);
}

int Map::GetStationID(StationName station){
    if(this->stationLookup.find(station) == stationLookup.end()){
        return -1;
    }
    return this->stationLookup[station];
}
int Map::Enumerate(){
    return this->curr_id++;
}

Station* Map::GetStationByID(int id){
    return stations[id];
}
Station* Map::AddStation(Station *station)
{   
    // Add a station to the map
    if(this->stationLookup.find(station->station_name) == stationLookup.end()){
        int id = Enumerate();
        stationLookup[station->station_name] = id;
        this->stations.push_back(station);
        station->id = id;
        return station;
    }
    else {
        int id = GetStationID(station->station_name);
        return GetStationByID(id);
    }
}

void Map::FindPath(StationID from, StationID to){
    std::cout << "Finding path from " << this->stations[from]->station_name << " to " << this->stations[to]->station_name << std::endl;
    // Find the shortest path between two stations
    std::vector<int> dist;
    std::vector<int> prev;
    std::vector<bool> visited;
    std::vector<int> path;
    for (int i = 0; i < this->stations.size(); i++){
        dist.push_back(INT_MAX);
        prev.push_back(-1);
        visited.push_back(false);
    }
    dist[from] = 0;
    for (int i = 0; i < this->stations.size(); i++){
        int u = -1;
        for (int j = 0; j < this->stations.size(); j++){
            if (!visited[j] && (u == -1 || dist[j] < dist[u])){
                u = j;
            }
        }
        if (dist[u] == INT_MAX){
            break;
        }
        visited[u] = true;
        for (auto connection: this->stations[u]->connections){
            int v = GetStationID(connection->to->station_name);
            int alt = dist[u] + connection->distance;
            if (alt < dist[v]){
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }
    for (int at = to; at != -1; at = prev[at]){
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    for (auto station_id: path){
        this->stations[station_id]->PrintStation();
    }
}