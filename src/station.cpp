#include "graph.h"
#include <algorithm>

Station::Station(StationName station_name)
{
    // Initialize the station
    this->station_name = station_name;
    this->connections = std::vector<Connection*>();
}

void Station::PrintStation(){
    std::cout << "Station: " << this->station_name 
    #if DEBUG
    << " ID: " << this->id 
    #endif
    << " (";
    for(auto line : this->lines){
        if(line != this->lines.back())
            std::cout << line->line_name << ", ";
        else
            std::cout << line->line_name;
    }
    std::cout << ")"  << std::endl;

}

void Station::AddConnection(Connection *connection)
{
    // Add a connection to the station
    this->connections.push_back(connection);
}
void Station::AddLine(Line* line) {
    auto find_line = std::find_if(this->lines.begin(), this->lines.end(),
                           [line](Line* l) { return l->line_name == line->line_name; });
    if (find_line == this->lines.end()) {
        // Line not found, so add it
        this->lines.push_back(line);
    }
}