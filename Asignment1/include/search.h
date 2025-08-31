#ifndef SEARCH_H
#define SEARCH_H
#include "state.h"
#include <string>
using namespace std ;

class Search{
    public:
    virtual ~Search() {};
    virtual string run(const State &initial_state) = 0 ;
};

#endif 