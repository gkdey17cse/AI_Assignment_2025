#include "search.h"
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

// Heuristic: prefer positions that minimize immediate cost
int calculateHeuristic(const Ship& ship, const Container& container, int stack, int tier) {
    int cost = 0;
    
    // Check if placing here would block containers with lower destinations
    for (int t = tier - 1; t >= 0; t--) {
        if (ship.layout[stack][t].id != -1 && 
            ship.layout[stack][t].destination < container.destination) {
            cost += 2; // Penalty for blocking earlier destination
        }
    }
    
    // Check weight distribution (heavier containers should be at bottom)
    if (tier > 0 && ship.layout[stack][tier-1].id != -1 && 
        ship.layout[stack][tier-1].weight < container.weight) {
        cost += 1; // Penalty for placing heavier container above lighter one
    }
    
    // Balance consideration
    int portWeight = 0, starboardWeight = 0;
    for (int s = 0; s < ship.width; s++) {
        for (int t = 0; t < ship.height; t++) {
            if (ship.layout[s][t].id != -1) {
                if (s < ship.width / 2) {
                    portWeight += ship.layout[s][t].weight;
                } else {
                    starboardWeight += ship.layout[s][t].weight;
                }
            }
        }
    }
    
    // Add to the lighter side
    if ((stack < ship.width / 2 && portWeight < starboardWeight) ||
        (stack >= ship.width / 2 && starboardWeight < portWeight)) {
        cost -= 1; // Reward for improving balance
    } else {
        cost += 1; // Penalty for worsening balance
    }
    
    return cost;
}

bool greedySearch(const vector<Container>& containers, Ship& ship, int& totalCost) {
    vector<Container> remaining = containers;
    int cost = 0;
    
    // Sort containers by destination (earliest first) and weight (heaviest first)
    sort(remaining.begin(), remaining.end(), [](const Container& a, const Container& b) {
        if (a.destination != b.destination) {
            return a.destination < b.destination;
        }
        return a.weight > b.weight;
    });
    
    for (const Container& container : remaining) {
        int bestStack = -1, bestTier = -1;
        int bestHeuristic = INT_MAX;
        
        // Find the best position for this container
        for (int s = 0; s < ship.width; s++) {
            for (int t = 0; t < ship.height; t++) {
                if (ship.layout[s][t].id == -1) {
                    int h = calculateHeuristic(ship, container, s, t);
                    if (h < bestHeuristic) {
                        bestHeuristic = h;
                        bestStack = s;
                        bestTier = t;
                    }
                    break; // Only consider the lowest available tier in each stack
                }
            }
        }
        
        if (bestStack == -1) {
            // No space found
            return false;
        }
        
        // Place the container
        ship.layout[bestStack][bestTier] = container;
        cost += 1; // Loading cost
    }
    
    totalCost = cost + calculateTotalCost(ship);
    return true;
}