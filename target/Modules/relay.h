#ifndef RELAY_H
#define RELAY_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

typedef struct _relay{
  uint16_t pin;/*GPIO_Pin_8 ~ 13*/
  uint32_t set;/*GPIO_BSRR_BS8~13*/
  uint32_t reset;/*GPIO_BSRR_BR8~13*/
} relay;

void relay_gpio_configuration(relay* R);
void relay_on(relay* R);
void delay();
void relay_off(relay* R);

#endif
