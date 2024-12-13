#ifndef BST_H
#define BST_H

#include "Graph.h"
#include <unordered_set>
#include <chrono> // For time-related parameters

// Function to perform the Bounded Search Tree (BST) algorithm for exact vertex cover
std::unordered_set<int> BST_VC(Graph& G, std::unordered_set<int>& cover, int k, 
                                const std::chrono::steady_clock::time_point& start_time, double time_limit);

#endif // BST_H
