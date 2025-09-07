#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>
#include <string>

struct Container
{
    int id;
    int weight;
    int destination;
};

struct Ship
{
    int height;                                 // number of tiers
    std::vector<std::vector<Container>> layout; // 2D grid of containers (4 columns: port1, port2, starboard1, starboard2)
};

// Global constraint value
extern int MAX_WEIGHT_DIFFERENCE;

// Function declarations
void parseInput(const std::string &filename, std::vector<Container> &containers, Ship &ship, int &maxWeightDiff);
bool isBlocked(const Ship &ship, int stack, int tier);
int calculateBalanceCost(const Ship &ship, int &portWeight, int &starboardWeight);
int calculateDestinationCost(const Ship &ship);
int calculateWeightDistributionCost(const Ship &ship);
int calculateTotalCost(const Ship &ship, int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost);
void printShip(const Ship &ship);
void writeOutput(const std::string &filename, const Ship &ship, int totalCost, int loadingCost, 
                 int balanceCost, int destinationCost, int weightCost, const std::string &algorithm, int maxWeightDiff);

#endif