#ifndef RUBIK_AUTOSOLVER_H
#define RUBIK_AUTOSOLVER_H

#include "motor_driver.h"

#define RAS_TRUE  1
#define RAS_FALSE 0

struct SolverConfig {
    unsigned int dummy; // TODO: to be filled
};

void init_autosolver(struct SolverConfig* config);

int get_autosolver_should_close();

// <  Motor Driver Config  >
//  GPIO Clock  : APB2_GPIOD
//  Common GPIO : GPIOD
//  Step Pin    : Pin 3
//  Enable Pin  : Pin 4
//  Dir Pin     : Pin 5
//  Timer Clock : APB1_TIM4
//  Timer Pin   : TIM4
struct MotorDriverConfig get_motor_default_config();

#endif