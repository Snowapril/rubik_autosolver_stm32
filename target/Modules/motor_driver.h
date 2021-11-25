#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"

// Use same GPIO pin for clock & each port
struct MotorDriverConfigure {
    unsigned int gpio_clock_pin;
    GPIO_TypeDef* step_port;
    unsigned int step_pin;
    GPIO_TypeDef* enable_port;
    unsigned int enable_pin;
    GPIO_TypeDef* dir_port;
    unsigned int dir_pin;
    TIM_TypeDef* timer_pin;
    unsigned int timer_clock_pin;
};

// Initialize motor driver with given configuration
void motor_driver_init(struct MotorDriverConfigure* config);

// If call this function with true, motor change direction to clockwise
void motor_driver_change_dir(struct MotorDriverConfigure* config, int clockwise);

// If call this function with true, motor start running
void motor_driver_change_state(struct MotorDriverConfigure* config, int enable);

#endif