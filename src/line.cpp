#include "graph.h"

Line::Line(std::string line_name)
{
    // Initialize the line
    this->line_name = line_name;
    this->root = NULL;
    this->tail = NULL;
}
void Line::PrintLine(){
    std::cout << "Line:  " << this->line_name << std::endl;
    std::cout << "Start: " << this->root->station_name << std::endl;
    std::cout << "End:   " << this->tail->station_name << std::endl;
    std::cout << std::endl;
}