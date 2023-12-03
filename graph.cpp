//
// Created by farid on 12/1/2023.
//
#include <iostream>
#include <unordered_map>
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
    void getGraphSize() {
        cout << "There are " << nodeAmt << " Nodes." << endl;
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
        auto startTime = high_resolution_clock::now();        unordered_map<int, int> distances;
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
};