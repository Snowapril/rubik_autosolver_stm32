#ifndef PRESSURE_H
#define PRESSURE_H

#include "stm32f10x_adc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

void clock_enable();
void adc_configuration();
void gpio_configuration();
void ADC1_2_IRQHandler();
void NVIC_Configure();
void get_value();

#endif
