#include "graph.h"


Map::Map()
{
    // Initialize the map
    this->stations = std::vector<Station*>();
    this->lines = std::vector<Line*>();
}
Connection::Connection(Station *from, Station *to, Line *line, int distance)
{
    // Initialize the connection
    this->from = from;
    this->to = to;
    this->distance = distance;
    this->line = line;
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
void Station::PrintStation(){
    std::cout << "Station: " << this->station_name << " ID: " << this->id << std::endl;
    for (auto connection: this->connections){
        std::cout 
        << "    Connection: " 
        << connection->from->station_name 
        << " -> " 
        << connection->to->station_name 
        << std::endl
        << "    Line: "
        << connection->line->line_name
        << " ("
        << connection->line->root->station_name
        << " -> "
        << connection->line->tail->station_name
        << ")"
        << std::endl
        << "    Distance: " 
        << connection->distance 
        << std::endl
        << std::endl
        ;
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
void Station::AddConnection(Connection *connection)
{
    // Add a connection to the station
    this->connections.push_back(connection);
}