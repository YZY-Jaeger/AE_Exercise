#include "BST.h"
#include <stdexcept> // For std::runtime_error
#include <chrono> // For time checking
#include <unordered_set>
std::unordered_set<int> BST_VC(Graph& G, std::unordered_set<int>& C, int k, const std::chrono::steady_clock::time_point& start_time, double time_limit) {
    // Check if we've exceeded the time limit
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_time = now - start_time;
    if (elapsed_time.count() > time_limit) {
        return {}; // Return empty set if time limit exceeded
    }

    // Base case 1: If the size of cover is equal to k and there are still edges left, return ∅
    if (C.size() == k && G.hasEdges()) {
        return {}; // No solution within this depth (can't add more vertices)
    }

    // Base case 2: If there are no edges left, return the current cover (valid vertex cover found)
    if (!G.hasEdges()) {
        return C; // Return the current cover if there are no edges left
    }

    int v = -1, w = -1;
    // Find the first edge in the graph (arbitrary selection of vertices)
    for (int i = 1; i <= G.getNumVertices(); ++i) {
        if (!G.neighbors(i).empty()) {
            v = i;
            w = G.neighbors(i).front();
            break;
        }
    }

    if (v == -1 || w == -1) {
        throw std::runtime_error("No edges found, but graph is inconsistent.");
    }

    // Branch 1: Include v in the cover
    C.insert(v);
    std::vector<int> removedEdges = G.removeVertex(v); // Modify the graph in place
    auto result1 = BST_VC(G, C, k, start_time, time_limit);
    G.restoreVertex(v, removedEdges); // Restore the vertex and edges
    C.erase(v); // Backtrack

    if (!result1.empty()) {
        return result1; // Return the result if found
    }

    // Branch 2: Include w in the cover
    C.insert(w);
    removedEdges = G.removeVertex(w); // Modify the graph in place
    auto result2 = BST_VC(G, C, k, start_time, time_limit);
    G.restoreVertex(w, removedEdges); // Restore the vertex and edges
    C.erase(w); // Backtrack

    if (!result2.empty()) {
        return result2; // Return the result if found
    }

    return {}; // Return empty if no solution found
}
