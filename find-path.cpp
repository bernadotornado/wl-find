#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "src/graph.cpp"
#include "src/parser.h"
using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 4)
    {
         cerr << "Usage: " << argv[0] << " <map> <start> <destination>" <<  endl;
        return 1;
    }
     string map_path = argv[1];
     string start = argv[2];
     string destination = argv[3];
     cout << "Map: " << map_path <<  endl;
     cout << "Start: " << start <<  endl;
     cout << "Destination: " << destination <<  endl;

    Map* map = ParseFile(map_path);
    if(map ==NULL){
        return 1;
    }
    auto startStation = map->GetStationID(start);
    auto endStation = map->GetStationID(destination);

    cout << "Start ID: " << startStation << "\nDestination ID: " << endStation <<endl;

    return 0;
}
