#include "search.h"
#include <queue>
#include <functional>
#include <iostream>

using namespace std;

struct State
{
    Ship ship;
    vector<Container> remainingContainers;
    int cost;      // g(n) - cost so far
    int heuristic; // h(n) - estimated cost to goal

    // For priority queue
    bool operator>(const State &other) const
    {
        return (cost + heuristic) > (other.cost + other.heuristic);
    }
};

// Heuristic function: estimate remaining cost
// Heuristic function: estimate remaining cost
int calculateHeuristic(const Ship &ship, const vector<Container> &remaining)
{
    int h = 0;

    // Estimate balance cost
    int portWeight = 0, starboardWeight = 0;
    for (int s = 0; s < ship.width; s++)
    {
        for (int t = 0; t < ship.height; t++)
        {
            if (ship.layout[s][t].id != -1)
            {
                if (s < ship.width / 2)
                {
                    portWeight += ship.layout[s][t].weight;
                }
                else
                {
                    starboardWeight += ship.layout[s][t].weight;
                }
            }
        }
    }

    // Add remaining containers to the lighter side (optimistic estimate)
    for (const Container &c : remaining)
    {
        if (portWeight < starboardWeight)
        {
            portWeight += c.weight;
        }
        else
        {
            starboardWeight += c.weight;
        }
    }

    int balanceDifference = abs(portWeight - starboardWeight);
    if (balanceDifference > MAX_WEIGHT_DIFFERENCE)
    {
        h += (balanceDifference - MAX_WEIGHT_DIFFERENCE) * 2;
    }

    // Estimate destination constraint violations
    // Minimum possible violations: at least 1 per container that's not at the top
    h += remaining.size() / 2;

    return h;
}
bool astarSearch(const vector<Container> &containers, Ship &ship, int &totalCost)
{
    priority_queue<State, vector<State>, greater<State>> pq;

    State initial;
    initial.ship = ship;
    initial.remainingContainers = containers;
    initial.cost = 0;
    initial.heuristic = calculateHeuristic(ship, containers);
    pq.push(initial);

    while (!pq.empty())
    {
        State current = pq.top();
        pq.pop();

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

        for (int s = 0; s < current.ship.width; s++)
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
                    newState.heuristic = calculateHeuristic(newState.ship, newRemaining);

                    pq.push(newState);

                    // Only need to place in first available tier in each stack
                    break;
                }
            }
        }
    }

    return false;
}