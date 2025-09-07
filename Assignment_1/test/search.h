#ifndef SEARCH_H
#define SEARCH_H

#include "helper.h"

// Search algorithm declarations
bool bfsSearch(const std::vector<Container> &containers, Ship &ship, int &totalCost,
               int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost);
bool dfsSearch(const std::vector<Container> &containers, Ship &ship, int &totalCost,
               int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost);
bool iddfsSearch(const std::vector<Container> &containers, Ship &ship, int &totalCost,
                 int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost);
bool greedySearch(const std::vector<Container> &containers, Ship &ship, int &totalCost,
                  int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost);
bool astarSearch(const std::vector<Container> &containers, Ship &ship, int &totalCost,
                 int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost);

#endif