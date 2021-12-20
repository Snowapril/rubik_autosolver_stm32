#include "motor_driver.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "system_stm32f10x.h"
#include "Common/utils.h"

static void motor_driver_init_gpio(struct MotorDriverConfig* config) {
    GPIO_InitTypeDef step_init_struct;
    step_init_struct.GPIO_Pin     = config->step_pin;
    step_init_struct.GPIO_Speed   = GPIO_Speed_50MHz;
    step_init_struct.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(config->step_port, &step_init_struct);
  
    GPIO_InitTypeDef enable_init_struct;
    enable_init_struct.GPIO_Pin     = config->enable_pin;
    enable_init_struct.GPIO_Speed   = GPIO_Speed_50MHz;
    enable_init_struct.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(config->enable_port, &enable_init_struct);

    GPIO_InitTypeDef dir_init_struct;
    dir_init_struct.GPIO_Pin     = config->dir_pin;
    dir_init_struct.GPIO_Speed   = GPIO_Speed_50MHz;
    dir_init_struct.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_Init(config->dir_port, &dir_init_struct);
}

void motor_driver_init(struct MotorDriverConfig* config) {
    motor_driver_init_gpio(config);    

    // Set initial state of motor driver
    motor_driver_change_dir(config, 0);
    motor_driver_change_state(config, 0);
}

void motor_driver_change_dir(struct MotorDriverConfig* config, int clockwise) {
    if (clockwise) {
        GPIO_ResetBits(config->dir_port, config->dir_pin);
    } else {
        GPIO_SetBits(config->dir_port, config->dir_pin);
    }
}

void motor_driver_change_state(struct MotorDriverConfig* config, int enable) {
    if (enable) {
        GPIO_SetBits(config->enable_port, config->enable_pin);
    } else {
        GPIO_ResetBits(config->enable_port, config->enable_pin);
    }
}

void motor_driver_rotate(struct MotorDriverConfig* config, int steps, 
                         int delay, int clockwise) {
    motor_driver_change_state(config, 0);
    motor_driver_change_dir(config, clockwise);
    for (int i = 0; i < steps; ++i) {
      GPIO_SetBits(config->step_port, config->step_pin);
      delay_us(delay);
      GPIO_ResetBits(config->step_port, config->step_pin);
      delay_us(delay);
    }
    motor_driver_change_state(config, 1);
}