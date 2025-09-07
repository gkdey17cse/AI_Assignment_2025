#include "search.h"
#include <fstream>
#include <queue>
#include <iostream>

using namespace std;

struct State
{
    Ship ship;
    vector<Container> remainingContainers;
    int cost;
};

bool bfsSearch(const vector<Container> &containers, Ship &ship, int &totalCost,
               int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost)
{
    queue<State> q;
    State initial;
    initial.ship = ship;
    initial.remainingContainers = containers;
    initial.cost = 0;
    q.push(initial);

    while (!q.empty())
    {
        State current = q.front();
        q.pop();

        // If all containers are loaded, check if this is a valid solution
        if (current.remainingContainers.empty())
        {
            loadingCost = current.cost;
            totalCost = calculateTotalCost(current.ship, loadingCost, balanceCost, destinationCost, weightCost);

            if (totalCost <= 20) // Increased threshold for more realistic solutions
            {
                ship = current.ship;
                return true;
            }
            continue;
        }

        // Try to place the next container in all possible positions
        Container nextContainer = current.remainingContainers.back();
        vector<Container> newRemaining = current.remainingContainers;
        newRemaining.pop_back();

        for (int s = 0; s < 4; s++) // 4 columns total
        {
            for (int t = 0; t < current.ship.height; t++)
            {
                if (current.ship.layout[s][t].id == -1)
                {
                    // Found an empty slot
                    State newState = current;
                    newState.ship.layout[s][t] = nextContainer;
                    newState.remainingContainers = newRemaining;
                    newState.cost += 1; // Loading cost

                    q.push(newState);
                    break; // Only consider the lowest available tier in each stack
                }
            }
        }
    }

    return false;
}