#ifndef PRESSURE_H
#define PRESSURE_H

#include "stm32f10x_adc.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_dma.h"
#include "misc.h"
#include <stdbool.h>

#define PRESSURE_WEIGHT 500;

typedef struct{
  GPIO_TypeDef* port;
  uint16_t pin;/*GPIO_Pin_1*/
} Pressure;

void pressure_init(Pressure* P);
bool pressure_check();
#endif
