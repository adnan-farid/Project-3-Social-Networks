//
// Created by farid on 12/1/2023.
//
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
class Graph{
private:
    unordered_map<int, vector<int>> adjacencyList;
public:
    void addEdge(int from, int to) {
        //(from -> to)
        adjacencyList[from].push_back(to);
        //add another edge (to -> from) because the graph is undirected
        adjacencyList[to].push_back(from);
    }
    void readDataset(const string &filename) {
        ifstream file(filename);
        string line;
        //get rid of first line in csv
        getline(file, line);
        while (getline(file, line)) {
            stringstream ss(line);
            string from, to;
            if(getline(ss, from, ',') && getline(ss,to)) {
                addEdge(stoi(from), stoi(to));
            }
        }
    }
    void printGraph() {
        for (auto& pair : adjacencyList) {
            cout << "Node " << pair.first << " connects to: ";
            for (int node : pair.second) {
                cout << node << " ";
            }
            cout << endl;
        }
    }
};