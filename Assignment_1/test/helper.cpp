#include "helper.h"
#include <fstream>
#include <sstream>

using namespace std;

// Initialize global variable
int MAX_WEIGHT_DIFFERENCE = 100;

void parseInput(const string &filename, vector<Container> &containers, Ship &ship, int &maxWeightDiff)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error: Could not open input file." << endl;
        return;
    }

    string line;
    // Read max weight difference constraint and ship height
    getline(file, line);
    stringstream ss(line);
    ss >> maxWeightDiff >> ship.height;
    MAX_WEIGHT_DIFFERENCE = maxWeightDiff;

    // Initialize ship layout with 4 columns (2 port, 2 starboard)
    ship.layout.resize(4, vector<Container>(ship.height, {-1, 0, 0}));

    // Read containers
    int id = 0;
    while (getline(file, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;

        stringstream ss(line);
        int weight, destination;
        if (ss >> weight >> destination)
        {
            containers.push_back({id++, weight, destination});
        }
    }

    file.close();

    // Debug: Print container count
    cout << "DEBUG: Parsed " << containers.size() << " containers" << endl;
}

bool isBlocked(const Ship &ship, int stack, int tier)
{
    for (int t = tier + 1; t < ship.height; t++)
    {
        if (ship.layout[stack][t].id != -1)
        {
            return true;
        }
    }
    return false;
}

int calculateBalanceCost(const Ship &ship, int &portWeight, int &starboardWeight)
{
    portWeight = 0;
    starboardWeight = 0;

    // Columns 0-1: Port side, Columns 2-3: Starboard side
    for (int s = 0; s < 4; s++)
    {
        for (int t = 0; t < ship.height; t++)
        {
            if (ship.layout[s][t].id != -1)
            {
                if (s < 2) // Port side (columns 0 and 1)
                {
                    portWeight += ship.layout[s][t].weight;
                }
                else // Starboard side (columns 2 and 3)
                {
                    starboardWeight += ship.layout[s][t].weight;
                }
            }
        }
    }

    int difference = abs(portWeight - starboardWeight);
    return difference > MAX_WEIGHT_DIFFERENCE ? (difference - MAX_WEIGHT_DIFFERENCE) * 2 : 0;
}

int calculateDestinationCost(const Ship &ship)
{
    int cost = 0;

    for (int s = 0; s < 4; s++)
    {
        for (int t = 0; t < ship.height; t++)
        {
            if (ship.layout[s][t].id != -1)
            {
                // Check if container is blocked by containers with higher destination
                for (int above = t + 1; above < ship.height; above++)
                {
                    if (ship.layout[s][above].id != -1 &&
                        ship.layout[s][above].destination > ship.layout[s][t].destination)
                    {
                        cost += 2; // Penalty for violation
                    }
                }
            }
        }
    }

    return cost;
}

int calculateWeightDistributionCost(const Ship &ship)
{
    int cost = 0;

    for (int s = 0; s < 4; s++)
    {
        for (int t = 0; t < ship.height - 1; t++)
        {
            if (ship.layout[s][t].id != -1 && ship.layout[s][t + 1].id != -1)
            {
                if (ship.layout[s][t].weight < ship.layout[s][t + 1].weight)
                {
                    cost += 1; // Penalty for lighter container below heavier one
                }
            }
        }
    }

    return cost;
}

int calculateTotalCost(const Ship &ship, int &loadingCost, int &balanceCost, int &destinationCost, int &weightCost)
{
    int portWeight, starboardWeight;
    balanceCost = calculateBalanceCost(ship, portWeight, starboardWeight);
    destinationCost = calculateDestinationCost(ship);
    weightCost = calculateWeightDistributionCost(ship);

    // Loading cost is calculated during the search process
    return loadingCost + balanceCost + destinationCost + weightCost;
}

void printShip(const Ship &ship)
{
    cout << "Ship Layout:" << endl;
    cout << "Port Side      Starboard Side" << endl;
    cout << "Col 0  Col 1   Col 2  Col 3" << endl;

    for (int t = ship.height - 1; t >= 0; t--)
    {
        for (int s = 0; s < 4; s++)
        {
            if (ship.layout[s][t].id == -1)
            {
                cout << "[ ] ";
            }
            else
            {
                cout << "[" << ship.layout[s][t].destination << "] ";
            }

            // Add space between port and starboard sides
            if (s == 1)
                cout << "  ";
        }
        cout << endl;
    }

    // Print weight information
    int portWeight, starboardWeight;
    calculateBalanceCost(ship, portWeight, starboardWeight);
    cout << "Port weight: " << portWeight << ", Starboard weight: " << starboardWeight;
    cout << ", Difference: " << abs(portWeight - starboardWeight) << endl;
}

void writeOutput(const string &filename, const Ship &ship, int totalCost, int loadingCost,
                 int balanceCost, int destinationCost, int weightCost, const string &algorithm, int maxWeightDiff)
{
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cerr << "Error: Could not open output file." << endl;
        return;
    }

    file << "Algorithm: " << algorithm << endl;
    file << "Max Weight Difference Allowed: " << maxWeightDiff << endl;
    file << "Total Cost: " << totalCost << " (Loading: " << loadingCost << ", Balance: " << balanceCost;
    file << ", Destination: " << destinationCost << ", Weight Dist: " << weightCost << ")" << endl;
    file << "Layout:" << endl;
    file << "Port Side      Starboard Side" << endl;
    file << "Col 0  Col 1   Col 2  Col 3" << endl;

    for (int t = ship.height - 1; t >= 0; t--)
    {
        for (int s = 0; s < 4; s++)
        {
            if (ship.layout[s][t].id == -1)
            {
                file << "[ ] ";
            }
            else
            {
                file << "[" << ship.layout[s][t].destination << "] ";
            }

            // Add space between port and starboard sides
            if (s == 1)
                file << "  ";
        }
        file << endl;
    }

    // Print weight information
    int portWeight, starboardWeight;
    calculateBalanceCost(ship, portWeight, starboardWeight);
    file << "Port weight: " << portWeight << ", Starboard weight: " << starboardWeight;
    file << ", Difference: " << abs(portWeight - starboardWeight) << endl;

    file << "-----------------------------" << endl;
    file.close();
}