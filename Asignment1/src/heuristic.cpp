#include <iostream>
#include "../include/heuristic.h"
#include <cmath>
using namespace std;
#include <vector>
#include <numeric>

int Heuristic::balance(const State &s)
{
    int num = s.side;                      // basically = 2
    int left_weight = 0, right_weight = 0; // initial weight of the both side of ship
    for (int i = 0; i < s.containers.size(); i++)
    {
        if (i < num)
        {
            left_weight = left_weight + s.containers[i]; // increasing left weight weight
        }
        else
        {
            right_weight = right_weight + s.containers[i]; // increasing right weight weight
        }
    }
    int weight_diff = abs(left_weight - right_weight);
    return weight_diff; // return difference of weight b/w port & STANBOARD
}
