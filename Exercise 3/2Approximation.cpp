#include "2Approximation.h"

std::unordered_set<int> vertexCover2Approximation(const Graph& graph) {
    std::unordered_set<int> cover;
    std::vector<bool> visited(graph.getNumVertices() + 1, false);

    for (int u = 1; u <= graph.getNumVertices(); ++u) {
        if (visited[u]) continue;

        for (int v : graph.neighbors(u)) {
            if (!visited[v]) {
                cover.insert(u);
                cover.insert(v);
                visited[u] = visited[v] = true;
                break;
            }
        }
    }
    return cover;
}
