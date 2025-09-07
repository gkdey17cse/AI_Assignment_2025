#include "search.h"
#include <stack>
#include <iostream>

using namespace std;

struct State
{
    Ship ship;
    vector<Container> remainingContainers;
    int cost;
};

bool dfsSearch(const vector<Container> &containers, Ship &ship, int &totalCost)
{
    stack<State> s;
    State initial;
    initial.ship = ship;
    initial.remainingContainers = containers;
    initial.cost = 0;
    s.push(initial);

    while (!s.empty())
    {
        State current = s.top();
        s.pop();

        // If all containers are loaded, check if this is a valid solution
        if (current.remainingContainers.empty())
        {
            int cost = calculateTotalCost(current.ship);
            if (cost <= 10)
            { // Threshold for acceptable solution
                ship = current.ship;
                totalCost = cost + current.cost;
                return true;
            }
            continue;
        }

        // Try to place the next container in all possible positions
        Container nextContainer = current.remainingContainers.back();
        vector<Container> newRemaining = current.remainingContainers;
        newRemaining.pop_back();

        for (int stack = 0; stack < current.ship.width; stack++)
        {
            for (int tier = 0; tier < current.ship.height; tier++)
            {
                if (current.ship.layout[stack][tier].id == -1)
                {
                    // Found an empty slot
                    State newState = current;
                    newState.ship.layout[stack][tier] = nextContainer;
                    newState.remainingContainers = newRemaining;
                    newState.cost += 1; // Loading cost

                    s.push(newState);

                    // Only need to place in first available tier in each stack
                    break;
                }
            }
        }
    }

    return false;
}