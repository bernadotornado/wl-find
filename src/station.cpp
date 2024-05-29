#include "graph.h"


Station::Station(StationName station_name)
{
    // Initialize the station
    this->station_name = station_name;
    this->connections = std::vector<Connection*>();
}

void Station::PrintStation(){
    std::cout << "Station: " << this->station_name << " ID: " << this->id << std::endl;
    for (auto connection: this->connections){
        connection->PrintConnection();
    }
}
void Station::AddConnection(Connection *connection)
{
    // Add a connection to the station
    this->connections.push_back(connection);
}