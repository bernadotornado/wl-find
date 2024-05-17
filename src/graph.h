#include <iostream>
#include <string>
#include <vector>
typedef std::string StationName;
class Station{
    public:
        StationName station_name;
        int distance;
        std::vector<Station*> connections;
        Station();
};

class Map{
    public:
        void AddLine(std::string line);
        void AddStation(StationName station_name);
        void AddConnection(StationName from, StationName to, int distance);
};