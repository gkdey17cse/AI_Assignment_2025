#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "helper.h"
#include "search.h"

using namespace std;

int main()
{
    vector<Container> containers;
    Ship ship;
    int maxWeightDiff;

    // Parse input
    parseInput("input.txt", containers, ship, maxWeightDiff);

    cout << "Max Weight Difference Allowed: " << maxWeightDiff << endl;
    cout << "Ship height: " << ship.height << " tiers" << endl;
    cout << "Containers to load: " << containers.size() << endl;
    cout << "Maximum capacity: " << (4 * ship.height) << " containers" << endl;

    // Clear output file
    ofstream clearFile("output.txt");
    clearFile.close();

    // Try different search algorithms
    Ship resultShip;
    int totalCost, loadingCost, balanceCost, destinationCost, weightCost;

    // BFS
    resultShip = ship;
    if (bfsSearch(containers, resultShip, totalCost, loadingCost, balanceCost, destinationCost, weightCost))
    {
        cout << "BFS found a solution with cost: " << totalCost << endl;
        cout << "Cost breakdown - Loading: " << loadingCost << ", Balance: " << balanceCost;
        cout << ", Destination: " << destinationCost << ", Weight Dist: " << weightCost << endl;
        printShip(resultShip);
        writeOutput("output.txt", resultShip, totalCost, loadingCost, balanceCost,
                    destinationCost, weightCost, "BFS", maxWeightDiff);
    }
    else
    {
        cout << "BFS did not find a solution" << endl;
    }

    // DFS
    resultShip = ship;
    if (dfsSearch(containers, resultShip, totalCost, loadingCost, balanceCost, destinationCost, weightCost))
    {
        cout << "DFS found a solution with cost: " << totalCost << endl;
        cout << "Cost breakdown - Loading: " << loadingCost << ", Balance: " << balanceCost;
        cout << ", Destination: " << destinationCost << ", Weight Dist: " << weightCost << endl;
        printShip(resultShip);
        writeOutput("output.txt", resultShip, totalCost, loadingCost, balanceCost,
                    destinationCost, weightCost, "DFS", maxWeightDiff);
    }
    else
    {
        cout << "DFS did not find a solution" << endl;
    }

    // IDDFS
    resultShip = ship;
    if (iddfsSearch(containers, resultShip, totalCost, loadingCost, balanceCost, destinationCost, weightCost))
    {
        cout << "IDDFS found a solution with cost: " << totalCost << endl;
        cout << "Cost breakdown - Loading: " << loadingCost << ", Balance: " << balanceCost;
        cout << ", Destination: " << destinationCost << ", Weight Dist: " << weightCost << endl;
        printShip(resultShip);
        writeOutput("output.txt", resultShip, totalCost, loadingCost, balanceCost,
                    destinationCost, weightCost, "IDDFS", maxWeightDiff);
    }
    else
    {
        cout << "IDDFS did not find a solution" << endl;
    }

    // Greedy
    resultShip = ship;
    if (greedySearch(containers, resultShip, totalCost, loadingCost, balanceCost, destinationCost, weightCost))
    {
        cout << "Greedy found a solution with cost: " << totalCost << endl;
        cout << "Cost breakdown - Loading: " << loadingCost << ", Balance: " << balanceCost;
        cout << ", Destination: " << destinationCost << ", Weight Dist: " << weightCost << endl;
        printShip(resultShip);
        writeOutput("output.txt", resultShip, totalCost, loadingCost, balanceCost,
                    destinationCost, weightCost, "Greedy", maxWeightDiff);
    }
    else
    {
        cout << "Greedy did not find a solution" << endl;
    }

    // A*
    resultShip = ship;
    if (astarSearch(containers, resultShip, totalCost, loadingCost, balanceCost, destinationCost, weightCost))
    {
        cout << "A* found a solution with cost: " << totalCost << endl;
        cout << "Cost breakdown - Loading: " << loadingCost << ", Balance: " << balanceCost;
        cout << ", Destination: " << destinationCost << ", Weight Dist: " << weightCost << endl;
        printShip(resultShip);
        writeOutput("output.txt", resultShip, totalCost, loadingCost, balanceCost,
                    destinationCost, weightCost, "A*", maxWeightDiff);
    }
    else
    {
        cout << "A* did not find a solution" << endl;
    }

    return 0;
}