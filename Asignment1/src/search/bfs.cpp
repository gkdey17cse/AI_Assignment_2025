#include "bfs.h"
#include <iostream>
#include <set>
#include <string>
#include <sstream>

// Helper to print a state
std::string state_to_string(const State& s) {
    std::stringstream ss;
    ss << s.side << ":";
    for (const auto& c : s.containers) {
        ss << "(" << c.weight << "," << c.dest_rank << ")";
    }
    return ss.str();
}

// Check if goal state is reached (all containers at their destination side)
bool is_goal(const State& s) {
    for (const auto& c : s.containers) {
        if (c.dest_rank != s.side) return false;
    }
    return true;
}

// Generate next possible states by flipping side of one container
std::vector<State> expand_state(const State& s) {
    std::vector<State> next_states;

    for (size_t i = 0; i < s.containers.size(); ++i) {
        if (s.containers[i].dest_rank != s.side) {
            State next = s;
            next.side = 1 - s.side; // flip side
            next_states.push_back(next);
        }
    }

    return next_states;
}

void BFS::search(const State& initial) {
    std::set<std::string> visited;
    q.push(initial);

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        std::string hash = state_to_string(current);
        if (visited.count(hash)) continue;
        visited.insert(hash);

        // Print current state
        std::cout << "Side " << current.side << " | Containers: ";
        for (const auto& c : current.containers) {
            std::cout << "(" << c.weight << "," << c.dest_rank << ") ";
        }
        std::cout << "\n";

        if (is_goal(current)) {
            std::cout << "Goal reached!\n";
            return;
        }

        std::vector<State> next_states = expand_state(current);
        for (auto& ns : next_states) {
            q.push(ns);
        }
    }

    std::cout << "No solution found.\n";
}
