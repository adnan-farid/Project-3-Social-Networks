#include <iostream>
#include "graph.cpp"
int main() {
    Graph graph;
    graph.readDataset("facebook_clean_data\\artist_edges.csv");
    graph.printGraph();
    return 0;
}
