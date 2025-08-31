#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
using namespace std;

// Simple struct for a container
struct Container
{
    int weight;
    int dest_rank;
};

class State
{
public:
    vector<Container> containers; // all containers
    int side;                     // number of bays per side
    int height;                   // max containers per bay
    int balanceLimit = 1000000;   // default large value
    int loadCost = 1;             // default cost per container load

    State() : side(0), height(0), balanceLimit(1000000), loadCost(1) {}

    void print() const;
    string to_string() const;
};


#endif
