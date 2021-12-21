#include "pressure.h"

volatile uint32_t PRESSURE_VALUE;

static void clock_enable(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

static void NVIC_Configure(){
  NVIC_InitTypeDef nvic;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  nvic.NVIC_IRQChannel = ADC1_2_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
  nvic.NVIC_IRQChannelSubPriority = 0x00;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
  ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
  ADC_Cmd(ADC1, ENABLE);
}

void pressure_init(Pressure* P){
  // enable required clock
  clock_enable();
  
  GPIO_InitTypeDef pressure_GPIO_InitStructure;
  pressure_GPIO_InitStructure.GPIO_Pin = P->pin;
  pressure_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  pressure_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(P->port, &pressure_GPIO_InitStructure);
  
  ADC_InitTypeDef ADC_InitStructure;
  ADC_DeInit(ADC1);
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 2;
  ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 2, ADC_SampleTime_55Cycles5);
  ADC_Init(ADC1, &ADC_InitStructure);
  
  ADC_ResetCalibration(ADC1);
  while(ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while(ADC_GetCalibrationStatus(ADC1));
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  
  // set required interrupt callback
  NVIC_Configure();
}
                     
void ADC1_2_IRQHandler(void) {
  PRESSURE_VALUE = ADC_GetConversionValue(ADC1);
  ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}

bool pressure_check(){
  printf("Pressure value : %d\n", PRESSURE_VALUE);
  return PRESSURE_VALUE >= PRESSURE_WEIGHT;
}
