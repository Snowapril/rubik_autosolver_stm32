#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

#define MOTOR_QUARTER_ANGLE 50
#define MOTOR_HALF_ANGLE 100
#define MOTOR_SPEED 10

// Use same GPIO pin for clock & each port
struct MotorDriverConfig {
    unsigned int gpio_clock_port;
    GPIO_TypeDef* common_gpio_port;
    unsigned int step_pin;
    unsigned int enable_pin;
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