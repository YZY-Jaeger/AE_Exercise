#include <iostream>
#include <chrono> // For measuring time
#include <string>
#include <unordered_set>
#include <fstream> // For file output
#include "Graph.h"
#include "2Approximation.h" // Include the combined 2Approximation header
#include "BST.h" // Include the BST header for exact algorithm

void run2Approximation();
void runBSTExact();
// Returns the size of the 2-approximation vertex cover
int getApproximateK(const std::string& filename) {
    Graph graph = parseGraph(filename);
    std::unordered_set<int> cover = vertexCover2Approximation(graph); // From 2Approximation.h
    return cover.size();  // Return the size of the vertex cover
}

int main() {
    std::cout << "Choose Algo:\n";
    std::cout << "[1] 2-Approx\n"
              << "[2] BST exact\n";

    std::string input;
    std::getline(std::cin, input);

    while(input != "1" && input != "2") {
        std::cout << "Invalid!\n\n";

        std::cout << "Choose Algo:\n";
        std::cout << "[1] 2-Approx\n"
                  << "[2] BST exact\n";
        std::getline(std::cin, input);
    }

    if (input == "1") {
        run2Approximation();
    } else if (input == "2") {
        runBSTExact();
    }

    return 0;
}

void run2Approximation() {
    std::ofstream outputFile("2approx_results.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    outputFile << "File,Vertex Cover Size,Computation Time (seconds)" << std::endl;

    for (int i = 1; i <= 200; ++i) {
        std::string filename = std::string("pace2019_track1_vc_exact_all/vc-exact_") + (i < 10 ? "00" : (i < 100 ? "0" : "")) + std::to_string(i) + ".gr";

        try {
            // Start measuring time
            auto start = std::chrono::high_resolution_clock::now();

            Graph graph = parseGraph(filename);
            std::unordered_set<int> cover = vertexCover2Approximation(graph);

            // Stop measuring time
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            std::cout << "File: " << filename << " | Vertex Cover Size: " << cover.size()
                      << " | Computation Time: " << duration.count() << " seconds" << std::endl;

            outputFile << filename << "," << cover.size() << "," << duration.count() << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Error processing file " << filename << ": " << e.what() << std::endl;
            outputFile << filename << ",Error," << e.what() << std::endl;
        }
    }

    outputFile.close();
    std::cout << "Results saved to 2approx_results.csv" << std::endl;
}

void runBSTExact() {
    std::ofstream outputFile("bst_exact_results.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return;
    }

    outputFile << "File,Vertex Cover Size,Computation Time (seconds)" << std::endl;

    const double TIME_LIMIT = 10.0;  // Set a time limit for each run (in seconds)

    for (int i = 1; i <= 200; ++i) {
        std::string filename = std::string("pace2019_track1_vc_exact_all/vc-exact_") + (i < 10 ? "00" : (i < 100 ? "0" : "")) + std::to_string(i) + ".gr";

        try {
            // Start time for this run using steady_clock
            auto start = std::chrono::steady_clock::now();

            Graph graph = parseGraph(filename);
            int k = getApproximateK(filename); // Get k from the 2-approximation or a default source

            std::unordered_set<int> cover;

            // Track time and check if we exceed the time limit
            cover = BST_VC(graph, cover, k, start, TIME_LIMIT); // Get the vertex cover from BST_VC

            if (!cover.empty()) {
                // Stop measuring time
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> duration = end - start;

                if (duration.count() > TIME_LIMIT) {
                    std::cerr << "Time limit exceeded for file " << filename << std::endl;
                    outputFile << filename << ",Error,Time limit exceeded" << std::endl;
                    continue;
                }

                std::cout << "File: " << filename << " | Vertex Cover Size: " << cover.size()
                          << " | Computation Time: " << duration.count() << " seconds" << std::endl;

                outputFile << filename << "," << cover.size() << "," << duration.count() << std::endl;
            } else {
                std::cerr << "Error processing file " << filename << ": No solution found" << std::endl;
                outputFile << filename << ",Error,No solution found" << std::endl;
            }

        } catch (const std::exception& e) {
            // Catch standard exceptions like recursion errors
            std::cerr << "Recursion error processing file " << filename << ": " << e.what() << std::endl;
            outputFile << filename << ",RE," << e.what() << std::endl;

        } catch (...) {
            // Catch any other types of exceptions (including segmentation fault errors)
            std::cerr << "Unknown error occurred for file " << filename << ". Skipping." << std::endl;
            outputFile << filename << ",RE,Unknown error" << std::endl;
        }
    }

    outputFile.close();
    std::cout << "Results saved to bst_exact_results.csv" << std::endl;
}
