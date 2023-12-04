//
// Created by farid on 12/1/2023.
//
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <limits>
#include <algorithm>
#include <set>
#include <chrono>
using namespace std;
class Graph{
private:
    unordered_map<int, vector<pair<int,int>>> adjacencyList;
    int nodeAmt;

    void setNodeAmt(int nodeAmt) {
        this->nodeAmt = nodeAmt;
    }
    void clearData() {
        adjacencyList.clear();
    }
public:
    Graph() {
        nodeAmt = 0;
    }
    void addEdge(int from, int to, int weight = 1) {
        //(from -> to)
        adjacencyList[from].push_back(make_pair(to, weight));
        //add another edge (to -> from) because the graph is undirected
        adjacencyList[to].push_back(make_pair(from, weight));
    }
    void readDataset(const string &filename) {
        clearData();
        ifstream file(filename);
        string line;
        //get rid of first line in csv
        getline(file, line);
        set<int> nodeCounter;
        while (getline(file, line)) {
            stringstream ss(line);
            string from, to;
            if(getline(ss, from, ',') && getline(ss,to)) {
                addEdge(stoi(from), stoi(to));
                nodeCounter.insert(stoi(from));
                nodeCounter.insert(stoi(to));
            }
        }
        setNodeAmt(nodeCounter.size());
    }
    double getGraphSize() {
        return nodeAmt;
    }
    void printGraph() {
        for (auto& pair : adjacencyList) {
            cout << "Node " << pair.first << " connects to: ";
            for (auto& edge : pair.second) {
                cout << edge.first << " ";
            }
            cout << endl;
        }
    }
    pair<int,vector<int>> dijkstra(int start, int end, double &executionTime) {
        using namespace std::chrono;
        auto startTime = high_resolution_clock::now();
        unordered_map<int, int> distances;
        unordered_map<int, int> before;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (auto& pair: adjacencyList) {
            distances[pair.first] = numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push(make_pair(0,start));

        while(!pq.empty()) {
            int curr = pq.top().second;
            pq.pop();
            if (curr == end) {
                break;
            }

            for (auto& adjacentNode : adjacencyList[curr]) {
                int next = adjacentNode.first;
                int weight = adjacentNode.second;
                int currDist = distances[curr] + weight;

                if (currDist < distances[next]) {
                    distances[next] = currDist;
                    before[next] = curr;
                    pq.push(make_pair(currDist, next));
                }
            }

        }
        vector <int> dijkstraPath;
        if (distances[end] != numeric_limits<int>::max()) {
            for (int i = end; i != start; i = before[i]) {
                dijkstraPath.push_back(i);
            }
            dijkstraPath.push_back(start);
            reverse(dijkstraPath.begin(), dijkstraPath.end());
        }
        auto endTime = high_resolution_clock::now();
        executionTime = duration<double>(endTime - startTime).count();
        return make_pair(distances[end], dijkstraPath);
    }

    pair<int, vector<int>> BFS(int start, int end, double &executionTime2) {
        using namespace std::chrono;
        auto startTime = high_resolution_clock::now();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //priority queue to look at nodes based on weights
        unordered_map<int, int> parent; //map to track parent of each node
        unordered_map<int, int> distances; //map to track total weight from start to each node

        unordered_set<int> visited; //set to keep track of visited nodes

        pq.push({0, start});
        distances[start] = 0;
        visited.insert(start);
        vector<int> path;
        while(!pq.empty()) {
            int curr_node = pq.top().second;
            int curr_weight = pq.top().first;
            pq.pop();
            //vector<int> path;
            //if the current node is the end node
            if (curr_node == end) {
                //vector<int> path;
                for (int n = end; n != start; n = parent[n]) {
                    path.push_back(n);
                }
                path.push_back(start);
                reverse(path.begin(), path.end());
                //return path;
                break;
            }

            //looks at neighbors of current node
            for (const auto &neighbor : adjacencyList[curr_node]) {
                int next = neighbor.first;
                int edge_weight = neighbor.second;
                int total = curr_weight + edge_weight;

                //if neighbor is not visited or new path is shorter, it updates
                if (visited.find(next) == visited.end() || total < distances[next]) {
                    pq.push({total, next});
                    parent[next] = curr_node;
                    distances[next] = total;
                    visited.insert(next);
                }
            }
        }
        auto endTime = high_resolution_clock ::now();
        executionTime2 = duration<double>(endTime - startTime).count();
        return make_pair(distances[end], path);
    }
};
