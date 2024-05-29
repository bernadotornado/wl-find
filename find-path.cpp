#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include "src/graph.cpp"
#include "src/connection.cpp"
#include "src/station.cpp"
#include "src/line.cpp"
#include "src/map.cpp"
#include "src/parser.h"
#include "src/debug.h"
using namespace std;

void Debug_Print(Map *map)
{
    for (auto station : map->stations)
    {
        station->PrintStation();
    }
    map->PrintMap();
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <map> <start> <destination>" << endl;
        return 1;
    }
    // Parse the command line arguments
    string map_path = argv[1];
    string start = argv[2];
    string destination = argv[3];
    cout << "Map: " << map_path << endl;
    cout << "Start: " << start << endl;
    cout << "Destination: " << destination << endl;
    // Parse the map file
    Map *map = ParseFile(map_path);
    if (map == NULL)
    {
        // Exit with an error if the map is invalid
        return 1;
    }
    int startStationID = map->GetStationID(start);
    int endStationID = map->GetStationID(destination);

#if DEBUG
    cout << "Start ID: " << startStationID << "\nDestination ID: " << endStationID << endl;
    Debug_Print(map);
#endif
    return 0;
}
