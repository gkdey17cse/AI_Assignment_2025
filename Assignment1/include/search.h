#ifndef SEARCH_H
#define SEARCH_H

#include "state.h"
#include <string>
#include <vector>

class Search {
public:
    virtual ~Search() {};
    virtual std::vector<State> run(const State& initial_state) = 0;
    virtual std::string getName() const = 0;
};

// Forward declarations for search algorithms
std::vector<State> breadthFirstSearch(const State& initial_state);
std::vector<State> depthFirstSearch(const State& initial_state);
std::vector<State> iterativeDeepeningDFS(const State& initial_state);
std::vector<State> greedySearch(const State& initial_state);
std::vector<State> aStarSearch(const State& initial_state);

#endif