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
void Map::AddStation(Station *station)
{
    // Add a station to the map
    this->stations.push_back(station);
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