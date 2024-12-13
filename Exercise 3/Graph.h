#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <fstream>
#include <sstream>

class Graph {
private:
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> adjList;

public:
    Graph(int n);
    void addEdge(int u, int v);
    const std::vector<int>& neighbors(int vertex) const;
    int getNumVertices() const;
    int getNumEdges() const;
};

Graph parseGraph(const std::string& filename);

#endif // GRAPH_H
