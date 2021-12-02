#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"

#include <string.h>

typedef struct BLUE_CONFIG{
    bool isValid;
    bool isATscan;
}BlueConfig;

void Bluetooth_Init(BlueConfig *config);

int  Bluetooth_send_data(const char *data, BlueConfig *config);

#endif