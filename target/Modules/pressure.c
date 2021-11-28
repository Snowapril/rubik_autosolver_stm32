#include "pressure.h"

uint16_t value = 0;

void clock_enable(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

void adc_configuration(){
  ADC_InitTypeDef adc;

  adc.ADC_Mode = ADC_Mode_Independent;
  adc.ADC_ScanConvMode = DISABLE; 
  adc.ADC_ContinuousConvMode = ENABLE; 
  adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
  adc.ADC_DataAlign = ADC_DataAlign_Right; 
  adc.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &adc);
  
  ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
  ADC_DMACmd(ADC1,ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_ResetCalibration(ADC1);
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1));
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void gpio_configuration(){
  GPIO_InitTypeDef pressure_GPIO_InitStructure;
  pressure_GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  pressure_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  pressure_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &pressure_GPIO_InitStructure);
}

void ADC1_2_IRQHandler(){
  if(ADC_GetITStatus(ADC1,ADC_IT_EOC)!=RESET) value = ADC_GetConversionValue(ADC1);
  ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}

void NVIC_Configure(){
  NVIC_InitTypeDef nvic;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  nvic.NVIC_IRQChannel = ADC1_2_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
  nvic.NVIC_IRQChannelSubPriority = 0x00;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
}

void get_value(){
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  val = ADC_GetConversionValue(ADC1);
  return value;
}
