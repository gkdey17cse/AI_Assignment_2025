#include <iostream>
#include "state.h"
#include <sstream>
using namespace std;
void STATE::print() const
{
    cout << "State || Side : " << side << " & Height : " << height << endl;
    cout << "Containers : ";
    for (auto container : containers)
    {
        cout << container << " ";
    }
    cout << endl;
}

string STATE::to_string() const
{
    ostringstream oss;
    oss << "Side : " << side << " Height : " << height << " Containers : ";
    for (auto container : containers)
    {
        oss << container << " ";
    }
    return oss.str();
}