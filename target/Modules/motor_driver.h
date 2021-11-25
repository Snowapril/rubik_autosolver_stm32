#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

// Use same GPIO pin for clock & each port
struct MotorDriverConfigure {
    unsigned int gpio_clock_pin;
    unsigned int step_port;
    unsigned int step_pin;
    unsigned int enable_port;
    unsigned int enable_pin;
    unsigned int dir_port;
    unsigned int dir_pin;
    unsigned int timer_pin;
    unsigned int timer_clock_pin;
};

// Initialize motor driver with given configuration
void motor_driver_init(struct MotorDriverConfigure* config);

// If call this function with true, motor change direction to clockwise
void motor_driver_change_dir(struct MotorDriverConfigure* config, int clockwise);

// If call this function with true, motor start running
void motor_driver_change_state(struct MotorDriverConfigure* config, int enable);

#endif