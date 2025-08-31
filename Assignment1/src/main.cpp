#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "state.h"
#include "search.h"
#include "bfs.h"

std::vector<Container> readContainersFromFile(const std::string& filename, int& num_bays, int& max_weight_diff, int& max_height) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        exit(1);
    }
    
    file >> num_bays >> max_weight_diff >> max_height;
    
    std::vector<Container> containers;
    int weight, destination;
    int id = 0;
    while (file >> weight >> destination) {
        containers.emplace_back(id++, weight, destination);
    }
    
    file.close();
    return containers;
}

void writeSolutionToFile(const std::string& filename, const State& solution) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create file " << filename << std::endl;
        return;
    }
    
    file << solution.toString();
    file.close();
}

// BFS implementation
std::vector<State> breadthFirstSearch(const State& initial_state) {
    BFS bfs;
    return bfs.run(initial_state);
}

int main() {
    // Try with small input first
    std::string input_file = "input.txt";
    
    int num_bays, max_weight_diff, max_height;
    std::vector<Container> containers = readContainersFromFile(input_file, num_bays, max_weight_diff, max_height);
    
    State initial_state(num_bays, max_weight_diff, max_height, containers);
    
    std::cout << "Initial state created with " << num_bays << " bays, max weight difference " 
              << max_weight_diff << ", max height " << max_height << ", and " << containers.size() << " containers." << std::endl;
    
    // Run BFS
    std::cout << "Running BFS..." << std::endl;
    std::vector<State> bfs_states = breadthFirstSearch(initial_state);
    
    // Find goal state
    int goal_index = -1;
    for (size_t i = 0; i < bfs_states.size(); i++) {
        if (bfs_states[i].isGoal()) {
            goal_index = i;
            break;
        }
    }
    
    if (goal_index != -1) {
        std::cout << "BFS Solution found!" << std::endl;
        writeSolutionToFile("results/solution_bfs.txt", bfs_states[goal_index]);
        std::cout << "Solution written to results/solution_bfs.txt" << std::endl;
        
        // Print the solution
        std::cout << "\nSolution:\n" << bfs_states[goal_index].toString() << std::endl;
    } else {
        std::cout << "No solution found with BFS." << std::endl;
    }
    
    return 0;
}