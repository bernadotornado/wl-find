#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
// #include "src/graph.cpp"
#include "src/connection.cpp"
#include "src/station.cpp"
#include "src/line.cpp"
#include "src/map.cpp"
#include "src/parser.h"
#include "src/debug.h"
using namespace std;

int main(int argc, char *argv[])
{
    // Check for the correct number of arguments
    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <map> <start> <destination>" << endl;
        return 1;
    }

    // Parse the command line arguments
    string map_path = argv[1];
    string start = argv[2];
    string destination = argv[3];

	// Print the command line arguments
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

	char sort;
	cout << "Which sorting algorithm would you like to use? (Type \"D\" for Dijkstra or \"B\" for BFS) " << endl;
	cin >> sort;

    int startStationID = map->GetStationID(start);
    int endStationID = map->GetStationID(destination);
    if(startStationID == -1){
        cerr << "Error: Station '"<< start << "' not found in map" << endl;
        return 1;
    }
    if(endStationID == -1){
        cerr << "Error: Station '"<< destination << "' not found in map" << endl;
        return 1;
    }

#if DEBUG
    Debug_Print(map);
    cout << "Start ID: " << startStationID << "\nDestination ID: " << endStationID << endl;
#endif
	if(tolower(sort) == 'd'){
		map->Dijkstra(startStationID, endStationID);
	}
	else if(tolower(sort) == 'b'){
		map->BFS(startStationID, endStationID);
	}
	else{
		cout << "Invalid sorting algorithm" << endl;
	}
    return 0;
}
