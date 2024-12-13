#include "Graph.h"
#include <random>
#include <algorithm> // Ensure this is included for std::remove
Graph::Graph(int n) : numVertices(n), numEdges(0) {
    adjList.resize(n + 1); // Vertices are indexed from 1
}

void Graph::addEdge(int u, int v) {
    if (u > numVertices || v > numVertices || u < 1 || v < 1) return;
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    numEdges++;
}

const std::vector<int>& Graph::neighbors(int vertex) const {
    return adjList[vertex];
}

int Graph::getNumVertices() const { 
    return numVertices; 
}

int Graph::getNumEdges() const { 
    return numEdges; 
}

// Checks if the graph has any edges
bool Graph::hasEdges() const {
    return numEdges > 0;
}

// Picks a random edge from the graph
std::pair<int, int> Graph::pickEdge() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, numVertices);

    // Loop until we find a valid edge
    while (true) {
        int u = dis(gen);
        if (adjList[u].empty()) continue;  // Skip if the vertex has no neighbors

        int v = adjList[u][dis(gen) % adjList[u].size()]; // Pick a random neighbor
        if (u != v) {
            return {u, v};
        }
    }
}


void Graph::removeNode(int v) {
    if (v < 1 || v > numVertices) return;

    // Remove all edges connected to vertex v
    for (int neighbor : adjList[v]) {
        auto& neighborsList = adjList[neighbor];
        // Use std::remove correctly to remove 'v' from neighbor's adjacency list
        neighborsList.erase(std::remove(neighborsList.begin(), neighborsList.end(), v), neighborsList.end());
        numEdges--; // Decrement the edge count for each edge removed
    }

    // Clear all the neighbors of vertex v
    adjList[v].clear(); 
    numEdges -= adjList[v].size(); // Update the number of edges after clearing
}


Graph parseGraph(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Error: Unable to open file.");
    }

    std::string line;
    int numVertices = 0, numEdges = 0;
    Graph graph(0); // Initialize an empty graph

    while (std::getline(infile, line)) {
        // Ignore comments and empty lines
        if (line.empty() || line[0] == 'c') continue;

        std::istringstream iss(line);
        if (line[0] == 'p') {
            // Parse the problem line to get the number of vertices and edges
            std::string problemType;
            iss >> problemType >> problemType >> numVertices >> numEdges;
            graph = Graph(numVertices); // Initialize graph with the correct number of vertices
        } else {
            // Parse edge lines and add edges to the graph
            int u, v;
            if (iss >> u >> v) {
                graph.addEdge(u, v);
            }
        }
    }

    return graph;
}

// Removes the vertex and all edges incident to it, returns the removed edges
std::vector<int> Graph::removeVertex(int v) {
    std::vector<int> removedEdges;

    if (v < 1 || v > numVertices) return removedEdges; // Invalid vertex

    // Remove all edges connected to vertex v and store them
    for (int neighbor : adjList[v]) {
        removedEdges.push_back(neighbor);
        auto& neighborsList = adjList[neighbor];
        neighborsList.erase(std::remove(neighborsList.begin(), neighborsList.end(), v), neighborsList.end());
        numEdges--; // One edge removed
    }
    adjList[v].clear(); // Remove all neighbors of v
    numEdges -= adjList[v].size(); // Update the number of edges

    return removedEdges;
}

// Restores the vertex and its incident edges
void Graph::restoreVertex(int v, const std::vector<int>& removedEdges) {
    if (v < 1 || v > numVertices) return; // Invalid vertex

    // Restore the edges that were removed
    for (int neighbor : removedEdges) {
        adjList[neighbor].push_back(v);
        adjList[v].push_back(neighbor);
        numEdges++; // Restoring edges
    }
}