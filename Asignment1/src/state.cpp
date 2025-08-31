#include <iostream>
#include "../include/state.h"
#include <sstream>
using namespace std;

void State::print() const
{
    cout << "State || Side: " << side << " & Height: " << height << endl;
    cout << "Containers (weight,dest_rank): ";
    for (auto &c : containers)
        cout << "(" << c.weight << "," << c.dest_rank << ") ";
    cout << endl;
}

string State::to_string() const
{
    ostringstream oss;
    oss << "Side: " << side << " Height: " << height << " Containers: ";
    for (auto &c : containers)
        oss << "(" << c.weight << "," << c.dest_rank << ") ";
    return oss.str();
}
