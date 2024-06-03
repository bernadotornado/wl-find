#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

typedef std::string StationName;
typedef int StationID;

class Connection;
class Station{
    public:
        int id;
        StationName station_name;
        std::vector<Connection*> connections;
        void AddConnection(Connection *connection);
        void PrintStation();
        Station(StationName station_name);
};
class Line{
    public:
        std::string line_name;
        Station *root;
        Station *tail;
        void PrintLine();
        Line(std::string line_name);

};
class Connection{
    public:
        Station *from;
        Station *to;
        int distance;
        // TODO: account for multiple lines
        Line *line;
        void PrintConnection();
        Connection *Reverse();
        Connection(Station *from, Station *to, Line *line, int distance);
};

class Map{
    private:
        int curr_id = 0;
        int Enumerate();
        std::map<StationName, int> stationLookup;
    public:
        std::vector<Station*> stations;
        std::vector<Line*> lines;
        Station* GetStationByID(int id);
        int      GetStationID(StationName station);
        void     AddLine(Line *line);
        Station* AddStation(Station *station);
        void     AddConnection(StationName from, StationName to, int distance);
        void     FindPath(StationID from, StationID to);
        void     PrintMap();
        Map();
};