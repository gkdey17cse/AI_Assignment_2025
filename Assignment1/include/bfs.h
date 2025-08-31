#ifndef BFS_H
#define BFS_H

#include "search.h"

class BFS : public Search
{
public:
    std::vector<State> run(const State &initial_state) override;
    std::string getName() const override;
};

#endif