#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>

struct Container
{
    int weight;
    int dest_rank;
};

// Overload >> for easy file reading
inline std::istream &operator>>(std::istream &in, Container &c)
{
    return in >> c.weight >> c.dest_rank;
}

#endif // CONTAINER_H
