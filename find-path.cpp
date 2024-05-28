#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "src/graph.cpp"
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

     ifstream map_file(map_path);
    if (!map_file)
    {
         cerr << "Error: cannot open file '" << map_path << "'" <<  endl;
        return 1;
    }
     string line;
    if (map_file.is_open())
    {
           
            #define FIND_LINE 1
            #define FIND_STATIONS 2
            #define FIND_DISTANCE 3
            #define OPEN_QUOTE 4
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
                if (state == FIND_LINE)
                {
                    current_token += line[i];
                    if (line[i] == ':')
                    {
                        Line *new_line = new Line(current_token);
                        current_line = new_line;
                        cout << "Line: " << current_token <<  endl;
                        map->AddLine(current_line);
                        current_token = "";
                        state = FIND_STATIONS;
                        continue;
                    }
                    continue;
                }
                if (state == FIND_STATIONS)
                {
                    if (line[i] == '\"')
                    {
                        state = OPEN_QUOTE;
                        continue;
                    }
                    continue;
                }
                if (state == OPEN_QUOTE)
                {
                    if (line[i] == '\"')
                    {
                        Station *station = new Station(current_token);
                        if(current_station != NULL){
                            current_station->AddConnection(station, current_distance);
                            current_distance = 0;
                        }
                        cout << "Station: " << current_token <<  endl;
                        current_station = station;
                        map->AddStation(station);
                        current_token = "";

                        state = FIND_DISTANCE;
                        continue;
                    }
                    current_token += line[i];
                    continue;
                }
                if(state == FIND_DISTANCE){
                    if(line[i] != ' '){
                        current_distance = line[i] - '0';
                        cout << "Distance: " << current_distance <<  endl;
                        state = FIND_STATIONS;
                        continue;
                    }
                    continue;
                }
                if(i == length - 1){
                    current_line = NULL;
                }
            }
        }
        for(auto i: map->lines){
            cout << i->line_name << endl;
        }
        for(auto i: map->stations){
            cout << i->station_name << endl;
        }

        map_file.close();
    }

    return 0;
}
