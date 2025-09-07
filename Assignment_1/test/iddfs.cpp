#include "search.h"
#include <iostream>

using namespace std;

struct State
{
    Ship ship;
    vector<Container> remainingContainers;
    int cost;
    int depth;
};

bool dls(State current, int depthLimit, Ship &resultShip, int &totalCost)
{
    if (current.remainingContainers.empty())
    {
        int cost = calculateTotalCost(current.ship);
        if (cost <= 15) // Increased threshold for more realistic solutions
        {
            resultShip = current.ship;
            totalCost = cost + current.cost;
            return true;
        }
        return false;
    }

    if (current.depth >= depthLimit)
    {
        return false;
    }

    // Try to place the next container in all possible positions
    Container nextContainer = current.remainingContainers.back();
    vector<Container> newRemaining = current.remainingContainers;
    newRemaining.pop_back();

    for (int s = 0; s < current.ship.width; s++)
    {
        for (int t = 0; t < current.ship.height; t++)
        {
            if (current.ship.layout[s][t].id == -1)
            {
                // Create a new state for each possible placement
                State newState = current;
                newState.ship.layout[s][t] = nextContainer;
                newState.remainingContainers = newRemaining;
                newState.cost += 1;
                newState.depth += 1;

                if (dls(newState, depthLimit, resultShip, totalCost))
                {
                    return true;
                }
                
                // Don't break here - we need to explore all positions
                // break;
            }
        }
    }

    return false;
}

bool iddfsSearch(const vector<Container> &containers, Ship &ship, int &totalCost)
{
    State initial;
    initial.ship = ship;
    initial.remainingContainers = containers;
    initial.cost = 0;
    initial.depth = 0;

    // Start from depth 0 up to number of containers
    for (int depthLimit = 0; depthLimit <= containers.size() * 2; depthLimit++)
    {
        Ship resultShip = ship; // Reset for each iteration
        int cost = 0;
        if (dls(initial, depthLimit, resultShip, cost))
        {
            ship = resultShip;
            totalCost = cost;
            return true;
        }
    }

    return false;
}