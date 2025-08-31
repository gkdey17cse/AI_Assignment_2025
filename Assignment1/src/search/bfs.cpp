#include "../../include/bfs.h"
#include <queue>
#include <unordered_set>
#include <iostream>
#include <string>
#include <chrono>

std::vector<State> BFS::run(const State& initial_state) {
    std::cout << "Starting BFS search..." << std::endl;
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::queue<int> frontier;
    std::vector<State> all_states;
    std::unordered_set<std::string> visited;
    
    // Add initial state
    all_states.push_back(initial_state);
    frontier.push(0);
    visited.insert(all_states[0].toString());
    
    int states_explored = 0;
    int max_queue_size = 1;
    
    while (!frontier.empty()) {
        // Update max queue size
        if (frontier.size() > max_queue_size) {
            max_queue_size = frontier.size();
        }
        
        int current_index = frontier.front();
        frontier.pop();
        State current_state = all_states[current_index];
        
        states_explored++;
        
        // Print progress every 1000 states
        if (states_explored % 1000 == 0) {
            auto current_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
            std::cout << "States explored: " << states_explored 
                      << ", Queue size: " << frontier.size()
                      << ", Time: " << duration.count() << "s" << std::endl;
        }
        
        if (current_state.isGoal()) {
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
            std::cout << "BFS completed in " << duration.count() << "ms" << std::endl;
            std::cout << "Total states explored: " << states_explored << std::endl;
            std::cout << "Max queue size: " << max_queue_size << std::endl;
            return all_states;
        }
        
        std::vector<State> successors = current_state.getSuccessors();
        for (const State& successor : successors) {
            std::string state_str = successor.toString();
            if (visited.find(state_str) == visited.end()) {
                visited.insert(state_str);
                all_states.push_back(successor);
                all_states.back().setParentIndex(current_index);
                frontier.push(all_states.size() - 1);
            }
        }
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "BFS completed in " << duration.count() << "ms (no solution found)" << std::endl;
    std::cout << "Total states explored: " << states_explored << std::endl;
    
    return all_states;
}

std::string BFS::getName() const {
    return "BFS";
}