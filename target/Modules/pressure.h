#ifndef PRESSURE_H
#define PRESSURE_H

#include "stm32f10x_adc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

#define WEIGHT 500;
uint16_t value = 0;

typedef struct{
  uint16_t pin;/*GPIO_Pin_0*/
  uint8_t channel;/*ADC_Channel_10 */
} pressure

void pressure_configuration(pressure* P);

#endif
