#include "graph.h"
Connection::Connection(Station *from, Station *to, Line *line, int distance)
{
    // Initialize the connection
    this->from = from;
    this->to = to;
    this->distance = distance;
    this->line = line;
}
void Connection::PrintConnection(){
    std::cout 
    << "Connection: " 
    << this->from->station_name 
    << " -> " 
    << this->to->station_name 
    << std::endl
    << "Line: "
    << this->line->line_name
    << " ("
    << this->line->root->station_name
    << " -> "
    << this->line->tail->station_name
    << ")"
    << std::endl
    << "Distance: " 
    << this->distance 
    << std::endl
    << std::endl
    ;
}