#include "Graph.h"

Graph::Graph(int n) : numVertices(n), numEdges(0) {
    adjList.resize(n + 1);
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

int Graph::getNumVertices() const { return numVertices; }
int Graph::getNumEdges() const { return numEdges; }

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
