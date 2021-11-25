#include "motor_driver.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "system_stm32f10x.h"

void motor_driver_init_clock(struct MotorDriverConfigure* config) {
    // Clock enable
    RCC_APB1PeriphClockCmd(config->timer_clock_pin, ENABLE);
	RCC_APB2PeriphClockCmd(config->gpio_clock_pin, ENABLE);
}

void motor_driver_init_timer(struct MotorDriverConfigure* config) {
    // Motor timer configure
    uint16_t prescale = (uint16_t) (SystemCoreClock / 1000000) - 1;
    TIM_TimeBaseInitTypeDef timer_init_structure;
    timer_init_structure.TIM_Period = 20000-1; 
    timer_init_structure.TIM_Prescaler = prescale;
    timer_init_structure.TIM_ClockDivision = 0;
    timer_init_structure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInit(config->timer_pin, &timer_init_structure);
    
    // Motor timer output & compare configure
    TIM_OCInitTypeDef timer_oc_init_structure;
    timer_oc_init_structure.TIM_OCMode = TIM_OCMode_PWM1;
    timer_oc_init_structure.TIM_OCPolarity = TIM_OCPolarity_High;
    timer_oc_init_structure.TIM_OutputState = TIM_OutputState_Enable;
    timer_oc_init_structure.TIM_Pulse = 1500; // us
    TIM_OC3Init(config->timer_pin, &timer_oc_init_structure);
    TIM_OC3PreloadConfig(config->timer_pin, TIM_OCPreload_Disable);
    
    TIM_ARRPreloadConfig(config->timer_pin, ENABLE);
    TIM_Cmd(config->timer_pin, ENABLE);
}  

void motor_driver_init_gpio(struct MotorDriverConfigure* config) {
    GPIO_InitTypeDef step_init_struct;
    step_init_struct.GPIO_Pin     = config->step_pin;
    step_init_struct.GPIO_Speed   = GPIO_Speed_50MHz;
    step_init_struct.GPIO_Mode    = GPIO_Mode_AF_PP;
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

void motor_driver_init(struct MotorDriverConfigure* config) {
    motor_driver_init_clock(config);
    motor_driver_init_timer(config);
    motor_driver_init_gpio(config);    

    // Set initial state of motor driver
    motor_driver_change_dir(config, 0);
    motor_driver_change_state(config, 1);
}

void motor_driver_change_dir(struct MotorDriverConfigure* config, int clockwise) {
    if (clockwise) {
        GPIO_ResetBits(config->dir_port, config->dir_pin);
    } else {
        GPIO_SetBits(config->dir_port, config->dir_pin);
    }
}

void motor_driver_change_state(struct MotorDriverConfigure* config, int enable) {
    if (enable) {
        GPIO_SetBits(config->enable_port, config->enable_pin);
    } else {
        GPIO_ResetBits(config->enable_port, config->enable_pin);
    }
}