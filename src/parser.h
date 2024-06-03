#include "graph.h"
#include <string>
// helpers
#define FIND_LINE 1
#define FIND_STATIONS 2
#define FIND_DISTANCE 3
#define OPEN_QUOTE 4
#define END_LINE line[i] == '\r' || line[i] == '\n'
#define NEXT_NOT_WHITESPACE line[i] != ' '
#define NEXT_QUOTE line[i] == '\"'
#define NEXT_COLON line[i] == ':'

using namespace std;
Map *ParseFile(std::string map_path)
{
    ifstream map_file(map_path);
    if (!map_file)
    {
        cerr << "Error: cannot open file '" << map_path << "'" << endl;
        return NULL;
    }
    string line;
    if (map_file.is_open())
    {
        int state = FIND_LINE;
        int current_distance = 0;
        string current_token = "";
        Line *current_line = NULL;
        Station *current_station = NULL;
        Map *map = new Map();

        // foreach line in the file
        while (getline(map_file, line))
        {
            // foreach character in the line
            for (int i = 0; i <  line.length(); i++)
            {
                if (END_LINE)
                {
                    // Reset the state
                    current_distance = 0;
                    current_line = NULL;
                    current_station = NULL;
                    current_token = "";
                    state = FIND_LINE;
                    break;
                }
                if (state == FIND_LINE)
                {
                    if (NEXT_COLON)
                    {
                        // Create a new line after finding the colon token
                        Line *new_line = new Line(current_token);
                        current_line = new_line;
                        #if DEBUG
                        cout << "Line: " << current_token << endl;
                        #endif
                        // Add the line to the map
                        map->AddLine(current_line);
                        // Reset the token
                        current_token = "";
                        // Move to the next state
                        state = FIND_STATIONS;
                        continue;
                    }
                    // Collect the line name
                    current_token += line[i];
                    continue;
                }
                if (state == FIND_STATIONS)
                {
                    if (NEXT_QUOTE)
                    {
                        // Move to the next state after finding the quote token
                        state = OPEN_QUOTE;
                        continue;
                    }
                    continue;
                }
                if (state == OPEN_QUOTE)
                {
                    if (NEXT_QUOTE)
                    {
                        // Create new Station or get the existing one
                        Station *station = new Station(current_token);
                        station = map->AddStation(station);
                        if (current_station != NULL)
                        {
                            // Create a new connection between the current station and the new station
                            Connection *connection = new Connection(current_station, station, current_line, current_distance);
                            current_station->AddConnection(connection);
                            current_station->AddConnection(connection->Reverse());
                            station->AddConnection(connection);
                            station->AddConnection(connection->Reverse());
                            station->AddLine(current_line);
                            current_distance = 0;
                        }
                        // Set the root of the line if it is not set
                        if(current_line->root == NULL){
                            current_line->root = station;
                        }
                        // Set the tail of the line
                        current_line->tail = station;
                        #if DEBUG
                        cout << "Station: " << current_token << endl;
                        #endif
                        current_station = station;
                        // Reset the token
                        current_token = "";
                        // Move to the next state
                        state = FIND_DISTANCE;
                        continue;
                    }
                    // Collect the station name
                    current_token += line[i];
                    continue;
                }
                if (state == FIND_DISTANCE)
                {
                    if (NEXT_NOT_WHITESPACE)
                    {
                        // Collect the distance (integer)
                        current_distance = line[i] - '0';
                        #if DEBUG
                        cout << "Distance: " << current_distance << endl;
                        #endif
                        // Move to the next state
                        state = FIND_STATIONS;
                        continue;
                    }
                    continue;
                }
            }
        }
        map_file.close();
        return map;
    }
    return NULL;
}
