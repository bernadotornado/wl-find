#include "graph.h"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <climits>
#include <algorithm>
#include <queue>
#include <utility>

Map::Map()
{
    // Initialize the map
    this->stations = std::vector<Station*>();
    this->lines = std::vector<Line*>();
}

void Map::PrintMap(){
    for (auto station: this->stations){
        station->PrintStation();
    }
    for (auto line: this->lines){
        line->PrintLine();
    }
}

void Map::AddLine(Line *line)
{
    this->lines.push_back(line);
}

int Map::GetStationID(StationName station){
    if(this->stationLookup.find(station) == stationLookup.end()){
        return -1;
    }
    return this->stationLookup[station];
}

int Map::Enumerate(){
    return this->curr_id++;
}

Station* Map::GetStationByID(int id){
    return stations[id];
}

Station* Map::AddStation(Station *station)
{
    // Add a station to the map
    if(this->stationLookup.find(station->station_name) == stationLookup.end()){
        int id = Enumerate();
        stationLookup[station->station_name] = id;
        this->stations.push_back(station);
        station->id = id;
        return station;
    }
    else {
        int id = GetStationID(station->station_name);
        return GetStationByID(id);
    }
}

void Map::Dijkstra(StationID from, StationID to){
    std::cout << "Finding path from " << this->stations[from]->station_name << " to " << this->stations[to]->station_name << std::endl;

    // priority queue to store the minimum distance
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::vector<int> dist(this->stations.size(), INT_MAX);
    std::vector<int> prev(this->stations.size(), -1);

	// set distance to the source station to 0
    dist[from] = 0;
    pq.push(std::make_pair(0, from));

	// process nodes until queue is empty
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == to) break; // Found the shortest path to the destination

	    // iterate over the connections of the current station
        for (auto connection: this->stations[u]->connections) {
            int v = GetStationID(connection->to->station_name);
            int weight = connection->distance;
			// compare distance of current station and weight of connection with distance of next station
            if (dist[u] + weight < dist[v]) {
				// update distance and add station to queue
                dist[v] = dist[u] + weight;
                pq.push(std::make_pair(dist[v], v));
                prev[v] = u;
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int at = to; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

	// print the path
    int totalTime = 0;
    if (path[0] == from) {
        for (size_t i = 0; i < path.size(); ++i) {
            this->stations[path[i]]->PrintStation(); // print every station
            if (i != path.size() - 1) {
                for (auto connection: this->stations[path[i]]->connections) {
                    if (connection->to->id == path[i + 1]) {
                        connection->PrintConnection();
                        totalTime += connection->distance; // add the distance to the total time

                        // Check for line transfer
                        if (i > 0) {
                            for (auto prevConnection: this->stations[path[i-1]]->connections) {
                                if (prevConnection->to->id == path[i] && prevConnection->line != connection->line) {
                                    std::cout << "Change trains from line " << prevConnection->line->line_name << " to line " << connection->line->line_name << std::endl;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        std::cout << "Total travel time: " << totalTime << " minutes" << std::endl;
    } else {
        std::cout << "No path found from " << this->stations[from]->station_name << " to " << this->stations[to]->station_name << std::endl;
    }
}

void Map::BFS(StationID from, StationID to) {
    std::cout << "Finding path from " << this->stations[from]->station_name << " to " << this->stations[to]->station_name << std::endl;

    // Queue for BFS
    std::queue<int> q;
    std::vector<bool> visited(this->stations.size(), false);
    std::vector<int> prev(this->stations.size(), -1);

    q.push(from);
    visited[from] = true;

	// while the queue is not empty - dequeue the front node and enqueue its neighbour nodes
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == to) break; // Found the path to the destination

		// iterate over the connections of the current station
        for (auto connection: this->stations[u]->connections) {
            int v = GetStationID(connection->to->station_name);

			// mark node as visited and enqueue it
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
                prev[v] = u;
            }
        }
    }

    // Reconstruct the path
    std::vector<int> path;
    for (int at = to; at != -1; at = prev[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());

 	// print the path
    if (path[0] == from) {
        int totalTime = 0;
        for (size_t i = 0; i < path.size(); ++i) {
            this->stations[path[i]]->PrintStation(); // print every station
            if (i != path.size() - 1) {
                for (auto connection: this->stations[path[i]]->connections) {
                    if (connection->to->id == path[i + 1]) {
                        connection->PrintConnection();
                        totalTime += connection->distance; // add the distance to the total time

                        // Check for line transfer
                        if (i > 0) {
                            for (auto prevConnection: this->stations[path[i-1]]->connections) {
                                if (prevConnection->to->id == path[i] && prevConnection->line != connection->line) {
                                    std::cout << "Change trains from line " << prevConnection->line->line_name << " to line " << connection->line->line_name << std::endl;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        std::cout << "Total travel time: " << totalTime << " minutes" << std::endl;
    } else {
        std::cout << "No path found from " << this->stations[from]->station_name << " to " << this->stations[to]->station_name << std::endl;
    }
}
