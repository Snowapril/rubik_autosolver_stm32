#ifndef RELAY_H
#define RELAY_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

typedef struct {
  unsigned int pin;
  unsigned int set;
  unsigned int reset;
} relay;

void relay_clock_enable();
void relay_gpio_configuration(relay* R);
void relay_on(relay* R);
void relay_off(relay* R);

#endif
