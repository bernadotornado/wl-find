#include "graph.h"
#include <string>

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
        while (getline(map_file, line))
        {
            int length = line.length();
            for (int i = 0; i < length; i++)
            {
                if (END_LINE)
                {
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
                        Line *new_line = new Line(current_token);
                        current_line = new_line;
                        cout << "Line: " << current_token << endl;
                        map->AddLine(current_line);
                        current_token = "";
                        state = FIND_STATIONS;
                        continue;
                    }
                    current_token += line[i];
                    continue;
                }
                if (state == FIND_STATIONS)
                {
                    if (NEXT_QUOTE)
                    {
                        state = OPEN_QUOTE;
                        continue;
                    }
                    continue;
                }
                if (state == OPEN_QUOTE)
                {
                    if (NEXT_QUOTE)
                    {
                        Station *station = new Station(current_token);
                        station = map->AddStation(station);
                        if (current_station != NULL)
                        {
                            current_station->AddConnection(station, current_distance);
                            current_distance = 0;
                        }
                        cout << "Station: " << current_token << endl;
                        current_station = station;
                        
                        current_token = "";

                        state = FIND_DISTANCE;
                        continue;
                    }
                    current_token += line[i];
                    continue;
                }
                if (state == FIND_DISTANCE)
                {
                    if (NEXT_NOT_WHITESPACE)
                    {
                        current_distance = line[i] - '0';
                        cout << "Distance: " << current_distance << endl;
                        state = FIND_STATIONS;
                        continue;
                    }
                    continue;
                }
            }
        }
        for (auto i : map->lines)
        {
            cout << i->line_name << endl;
        }
        map_file.close();
        return map;
    }
    return NULL;
}
