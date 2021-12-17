#ifndef GYRO_H
#define GYRO_H

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include <stdio.h>
#include <stdlib.h>

// mpu6050의 i2c 주소값은 0x68

#define I2C1_SLAVE_ADDRESS7    0x30
#define I2C2_SLAVE1_ADDRESS7   0x30
#define Gyro_BufferSize             4 
#define Gyro_ClockSpeed             200000
#define CR1_PE_Set              ((u16)0x0001)
#define CR1_PE_Reset            ((u16)0xFFFE)
#define I2C_SCL_pin GPIO_Pin_6
#define I2C_SDA_pin GPIO_Pin_7

#define MPU_ADDR 0x68
/*
GYRO
GPIOB
SCL = PB6
SDA = PB7

*/

char Gyro_Data[8];
uint8_t countx=0;

void gyro_RCC_Configuration();
void gyro_GPIO_Configuration();
void gyro_I2C1_Configuration();

// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=alsrb968&logNo=220733739953
// iic 통신 으로 가속도 센서 읽기 AHRS모듈 이용 이것을 수정하자. si
// single_byte read 이용
void I2C_start_Tx(I2C_TypeDef* I2Cx,uint8_t address, uint8_t direction);
void I2C_start_Rx(I2C_TypeDef* I2Cx,uint8_t address,uint8_t direction);
void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
void I2C_stop(I2C_TypeDef* I2Cx);
uint8_t myMPU6050Read(uint8_t reg);
float C_Accel_Z();
void gyro_start();


#endif