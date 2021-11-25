#include "rubik_autosolver.h"

int main(void)
{
    struct SolverConfig config = {
        10 // dummy value
    };

    // initialize rubik cube auto solver
    init_autosolver(&config);

    while (get_autosolver_should_close() !=  RAS_TRUE) {
        // Do stuff
    }
    
    return 0;
}
