#ifndef PRESSURE_H
#define PRESSURE_H

#include "stm32f10x_adc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include <stdbool.h>

#define PRESSURE_WEIGHT 500;

typedef struct{
  uint16_t pin;/*GPIO_Pin_0*/
  uint8_t channel;/*ADC_Channel_10 */
} pressure;

void pressure_init(pressure* P);
bool pressure_check();

#endif
