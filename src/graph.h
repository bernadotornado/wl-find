#include <iostream>
#include <string>
#include <vector>
#include <map>
typedef std::string StationName;
class Connection;
class Station{
    public:
        int id;
        StationName station_name;
        std::vector<Connection*> connections;
        Station(StationName station_name);
        void AddConnection(Station *to, int distance);
};
class Connection{
    public:
        Station *from;
        Station *to;
        int distance;
        Connection();
};
class Line{
    public:
        std::string line_name;
        Station *root;
        Station *tail;
        Line(std::string line_name);
};
class Map{
    private:
        int curr_id = 0;
        int Enumerate();
        std::map<StationName, int> stationLookup;
    public:
        std::vector<Station*> stations;
        std::vector<Line*> lines;
        Map();
        Station* GetStationByID(int id);
        int GetStationID(StationName station);
        void AddLine(Line *line);
        Station* AddStation(Station *station);
        void AddConnection(StationName from, StationName to, int distance);
};