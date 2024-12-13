#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <random> // For random edge selection

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
    bool hasEdges() const; // Check if the graph has edges
    std::pair<int, int> pickEdge(); // Pick a random edge
    void removeNode(int v); // Remove a node and its edges
    std::vector<int> removeVertex(int v);  // Removes the vertex and returns removed edges
    void restoreVertex(int v, const std::vector<int>& removedEdges);  // Restores the vertex and its edges
};

Graph parseGraph(const std::string& filename);

#endif // GRAPH_H
