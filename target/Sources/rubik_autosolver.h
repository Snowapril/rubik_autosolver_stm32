#ifndef RUBIK_AUTOSOLVER_H
#define RUBIK_AUTOSOLVER_H

#define RAS_TRUE  1
#define RAS_FALSE 0

struct SolverConfig {
    unsigned int dummy; // TODO: to be filled
};

void init_autosolver(struct SolverConfig* config);

int get_autosolver_should_close();

#endif