#include "gyro.h"
#include "stm32f10x_i2c.h"
void gyro_RCC_Configuration() {
  //GPIOB clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  //I2C2 clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
}

void gyro_GPIO_Configuration(struct GyroConfig* config) {
  GPIO_InitTypeDef gyro_GPIO_InitStructure;
  //SCL SDA configuration I2C2 using, SCL = PB10, SDA = PB11
  gyro_GPIO_InitStructure.GPIO_Pin = config->SCL_pin | config->SDA_pin;
  gyro_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  gyro_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &gyro_GPIO_InitStructure);
}

void gyro_I2C2_Configuration() {
  I2C_InitTypeDef  gyro_I2C_InitStructure;
  I2C_Cmd(I2C2,ENABLE);
  gyro_I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  gyro_I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  gyro_I2C_InitStructure.I2C_OwnAddress1 = I2C2_SLAVE1_ADDRESS7;
  gyro_I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  gyro_I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  gyro_I2C_InitStructure.I2C_ClockSpeed = ClockSpeed;
  I2C_Init(I2C2, &gyro_I2C_InitStructure);
}



void gyro_READ_DATA() {
  
}

