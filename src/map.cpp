#include "graph.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>

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