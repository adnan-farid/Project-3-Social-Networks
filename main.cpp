#include <iostream>
#include "graph.cpp"
int main() {
    Graph graph;
    graph.readDataset("facebook_clean_data\\artist_edges.csv");
    graph.getGraphSize();
    double executionTime;
    auto result = graph.dijkstra(1324, 50325, executionTime);
    cout << "Execution time: " << executionTime << " seconds" << endl;
    int shortestDistance = result.first;
    vector<int> shortestPath = result.second;

    cout << "Shortest distance: " << shortestDistance << endl;
    cout << "Shortest path: ";
    for (int node : shortestPath) {
        cout << node << " ";
    }
    return 0;
}
