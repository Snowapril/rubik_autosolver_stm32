#ifndef RUBIK_AUTOSOLVER_H
#define RUBIK_AUTOSOLVER_H

#include "motor_driver.h"
#include "bluetooth.h"

#define RAS_TRUE  1
#define RAS_FALSE 0

struct SolverConfig {
    BlueConfig bluetooth_config;
    struct MotorDriverConfig motor_driver_config;
};

void init_autosolver(struct SolverConfig* config);

int get_autosolver_should_close();

#endif