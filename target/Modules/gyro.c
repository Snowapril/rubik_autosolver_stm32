#include "gyro.h"
#include "Common/utils.h"

void gyro_RCC_Configuration() {
  
  //GPIOB clock enable
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  //I2C2 clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}

void gyro_GPIO_Configuration() {
  GPIO_InitTypeDef gyro_GPIO_InitStructure;
  //SCL SDA configuration I2C2 using, SCL = PB6, SDA = PB7
  gyro_GPIO_InitStructure.GPIO_Pin = I2C_SCL_pin | I2C_SDA_pin;
  gyro_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  gyro_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &gyro_GPIO_InitStructure);
}

void gyro_I2C1_Configuration() {
  I2C_InitTypeDef  gyro_I2C_InitStructure;
  I2C_Cmd(I2C1,DISABLE); // 초기화
  //I2C_Cmd(I2C1,ENABLE);
  gyro_I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  gyro_I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  gyro_I2C_InitStructure.I2C_OwnAddress1 = I2C1_SLAVE_ADDRESS7;
  gyro_I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
  gyro_I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  gyro_I2C_InitStructure.I2C_ClockSpeed = Gyro_ClockSpeed;
  I2C_Init(I2C1, &gyro_I2C_InitStructure);
  I2C_Cmd(I2C1,ENABLE);
}

void I2C_start_Tx(I2C_TypeDef* I2Cx,uint8_t address, uint8_t direction) {
  while(I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2Cx,ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx,address,direction);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
}

void I2C_start_Rx(I2C_TypeDef* I2Cx,uint8_t address,uint8_t direction) {
  I2C_GenerateSTART(I2Cx,ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2Cx,address,direction);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
}

void I2C_write(I2C_TypeDef* I2Cx, uint8_t data) {
  I2C_SendData(I2Cx,data);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

uint8_t I2C_read_ack(I2C_TypeDef* I2Cx) {
  I2C_AcknowledgeConfig(I2Cx,ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));
  uint8_t data = I2C_ReceiveData(I2Cx);
  return data;
}
uint8_t I2C_read_nack(I2C_TypeDef* I2Cx) {
  I2C_AcknowledgeConfig(I2Cx,DISABLE);
  I2C_GenerateSTOP(I2Cx,ENABLE);
  while(!I2C_CheckEvent(I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));
  uint8_t data = I2C_ReceiveData(I2Cx);
  return data;
}

void I2C_stop(I2C_TypeDef* I2Cx) {
  I2C_GenerateSTOP(I2Cx,ENABLE);
}


uint8_t myMPU6050Read(uint8_t reg) {
  unsigned char data = 0;
  I2C_start_Tx(I2C1,I2C1_SLAVE_ADDRESS7 << 1, I2C_Direction_Transmitter);
  I2C_write(I2C1, reg);
  I2C_start_Rx(I2C1, I2C1_SLAVE_ADDRESS7 << 1, I2C_Direction_Receiver);
  data = I2C_read_nack(I2C1);
  I2C_stop(I2C1);
  return data;
} // 여기 고쳐야 할수도

float C_Accel_Z() {
  uint16_t HighBit,LowBit,RawData;
  float data;
  HighBit = myMPU6050Read(MPU_ADDR);
  LowBit = myMPU6050Read(MPU_ADDR+1);
  RawData = HighBit << 8 | LowBit;
  data = (float)RawData; // raw data 받기
  return data;
} // 여기 고쳐야 할수도

void gyro_start() {
  gyro_RCC_Configuration();
  gyro_GPIO_Configuration();
  gyro_I2C1_Configuration();
  float AccelData;
  while(1) {
    AccelData = C_Accel_Z();
    printf("AccelData = %f\n",AccelData);
  }
}






/*
void I2C_SET() {
  I2C1->CR1 = CR1_PE_Set;
}
void I2C_RESET() {
  I2C1->CR1 = CR1_PE_Reset;
}


void gyro_READ_DATA() {
  I2C_GenerateSTART(I2C1,ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, I2C2_SLAVE1_ADDRESS7, I2C_Direction_Transmitter);
  while(1) {
    if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)) {
      Gyro_Data[countx] = I2C_ReceiveData(I2C1);
      countx++;
    }
    delay();
    if(countx == 7) {
      break;
    }
  }
}

void gyro_PRINT_DATA() {
  int i = 0;
  printf("Gyro_Data : ");
  for(i = 0; i < 8; i++) {
    printf("%c ",Gyro_Data[i]);
  }
  printf("\n");
  
}
*/
