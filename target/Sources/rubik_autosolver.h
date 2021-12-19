#ifndef RUBIK_AUTOSOLVER_H
#define RUBIK_AUTOSOLVER_H

#include "motor_driver.h"
#include "bluetooth.h"

enum AppState {
  APP_IDLE = 0,
  APP_SOLVING = 1,
};

#define RAS_TRUE  1
#define RAS_FALSE 0

struct SolverConfig {
    BlueConfig bluetooth_config;
    struct MotorDriverConfig motor_driver_configs[6];
};

// initialize modules with given configures
void init_autosolver(struct SolverConfig* config);

// check this program should close or not
int get_autosolver_should_close();

// main loop of this program
void loop(struct SolverConfig* config);

#endif