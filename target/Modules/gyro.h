#ifndef GYRO_H
#define GYRO_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

#define I2C1_SLAVE_ADDRESS7    0x30
#define I2C2_SLAVE1_ADDRESS7   0x30
#define BufferSize             4 
#define ClockSpeed             200000

void gyro_RCC_Configuration();
void gyro_GPIO_Configuration();
void gyro_I2C2_Configuration();


#endif