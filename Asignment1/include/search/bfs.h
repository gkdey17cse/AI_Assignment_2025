#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include "container.h"

// State of the container stacks
struct State {
    std::vector<Container> containers;
    int side; // example: 0 or 1
};

// BFS search class
class BFS {
public:
    BFS() = default;
    ~BFS() = default;

    void search(const State& initial);

private:
    std::queue<State> q;
};

#endif // BFS_H
