#define SEARCH_H
#include "state.h"
#include <string>
using namespace std ;

class SEARCH{
    public:
    virtual ~ Search() {};
    virtual string run(const STATE &initial_state) = 0 ;
};

#endif 