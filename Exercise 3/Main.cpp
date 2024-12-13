#include <iostream>
#include <chrono> // For measuring time
#include <string>
#include <unordered_set>
#include <fstream> // For file output
#include "Graph.h"
#include "2Approximation.h" // Include the combined 2Approximation header

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
        
    // Open a CSV file for output
    std::ofstream outputFile("2approx_results.csv");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open output file." << std::endl;
        return 1; // Exit if the file cannot be opened
    }

    // Write the header to the CSV file
    outputFile << "File,Vertex Cover Size,Computation Time (seconds)" << std::endl;

    for (int i = 1; i <= 200; ++i) {
        // Construct the filename based on the index
        std::string filename = std::string("pace2019_track1_vc_exact_all/vc-exact_") + (i < 10 ? "00" : (i < 100 ? "0" : "")) + std::to_string(i) + ".gr";

        try {
            // Start measuring time
            auto start = std::chrono::high_resolution_clock::now();

            Graph graph = parseGraph(filename);
            std::unordered_set<int> cover = vertexCover2Approximation(graph);

            // Stop measuring time
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;

            // Output the results to the console
            std::cout << "File: " << filename << " | Vertex Cover Size: " << cover.size() 
                      << " | Computation Time: " << duration.count() << " seconds" << std::endl;

            // Write the results to the CSV file
            outputFile << filename << "," << cover.size() << "," << duration.count() << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "Error processing file " << filename << ": " << e.what() << std::endl;
            // Optionally, you can log the error to the CSV file as well
            outputFile << filename << ",Error," << e.what() << std::endl;
        }
    }

    // Close the output file
    outputFile.close();
    std::cout << "Results saved to vertex_cover_results.csv" << std::endl;

    } else if (input == "2") {
        // do something else
    }

    return 0;
}
