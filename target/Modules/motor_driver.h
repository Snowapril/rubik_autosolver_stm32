#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

#define MOTOR_QUARTER_ANGLE 50
#define MOTOR_HALF_ANGLE 100
#define MOTOR_SPEED 10000

// Use same GPIO pin for clock & each port
struct MotorDriverConfig {
    GPIO_TypeDef* step_port;
    unsigned int step_pin;
    GPIO_TypeDef* enable_port;
    unsigned int enable_pin;
    GPIO_TypeDef* dir_port;
    unsigned int dir_pin;
};

// Initialize motor driver with given configuration
void motor_driver_init(struct MotorDriverConfig* config);

// If call this function with true, motor change direction to clockwise
void motor_driver_change_dir(struct MotorDriverConfig* config, int clockwise);

// If call this function with true, motor start running
void motor_driver_change_state(struct MotorDriverConfig* config, int enable);

// rotate motor with given angle, speed and clockwise
void motor_driver_rotate(struct MotorDriverConfig* config, int angle, 
                         int speed, int clockwise);

#endif