#include "graph.h"


Map::Map()
{
    // Initialize the map
    this->stations = std::vector<Station*>();
    this->lines = std::vector<Line*>();
}
Connection::Connection()
{
    // Initialize the connection
    this->from = NULL;
    this->to = NULL;
    this->distance = 0;
}
Line::Line(std::string line_name)
{
    // Initialize the line
    this->line_name = line_name;
    this->root = NULL;
    this->tail = NULL;
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
void Map::AddLine(Line *line)
{
    // Add a line to the map
    this->lines.push_back(line);
}

Station::Station(StationName station_name)
{
    // Initialize the station
    this->station_name = station_name;
    this->connections = std::vector<Connection*>();
}
void Station::AddConnection(Station *to, int distance)
{
    // Add a connection to the station
    Connection *connection = new Connection();
    connection->from = this;
    connection->to = to;
    connection->distance = distance;
    this->connections.push_back(connection);
}