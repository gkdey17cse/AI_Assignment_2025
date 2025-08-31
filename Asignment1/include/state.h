#ifndef STATE_H
#define STATE_H
#include <vector>
#include <string>
using namespace std;
class STATE
{
public:
    vector<int> containers; // presents all the containers
    int side;               // sides are two // 1. port and another is 2. standbord
    int height;             // height means max no of container in each bays

    STATE()
    {
        this->side = 0,
        this->height = 0;
    }

    void print() const; // print state in the consule

    string to_string() const; // convert state to string for saving purpose
};

#endif
