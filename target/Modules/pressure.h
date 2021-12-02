#ifndef PRESSURE_H
#define PRESSURE_H

#include "stm32f10x_adc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

typedef struct{
  uint16_t pin;/*GPIO_Pin_0*/
  uint8_t channel;/*ADC_Channel_10 */
} pressure

void clock_enable();
void adc_configuration(struct pressure* P);
void gpio_configuration(struct pressure* P);
void ADC1_2_IRQHandler();
void NVIC_Configure();
void get_value();

#endif
