#include "pressure.h"

volatile uint32_t PRESSURE_VALUE = 0;

static void clock_enable(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

static void NVIC_Configure(){
  NVIC_InitTypeDef nvic;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  nvic.NVIC_IRQChannel = ADC1_2_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 0x00;
  nvic.NVIC_IRQChannelSubPriority = 0x00;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
}

void pressure_init(pressure* P){
  // enable required clock
  clock_enable();
  
  // set required interrupt callback
  NVIC_Configure();
  
  ADC_InitTypeDef adc;

  adc.ADC_Mode = ADC_Mode_Independent;
  adc.ADC_ScanConvMode = DISABLE; 
  adc.ADC_ContinuousConvMode = ENABLE; 
  adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
  adc.ADC_DataAlign = ADC_DataAlign_Right; 
  adc.ADC_NbrOfChannel = 1;
  ADC_Init(ADC1, &adc);
  
  ADC_RegularChannelConfig(ADC1, P->channel, 1, ADC_SampleTime_239Cycles5);
  ADC_DMACmd(ADC1,ENABLE);
  ADC_Cmd(ADC1, ENABLE);
  ADC_ResetCalibration(ADC1);
  while (ADC_GetResetCalibrationStatus(ADC1));
  ADC_StartCalibration(ADC1);
  while (ADC_GetCalibrationStatus(ADC1));
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  
  GPIO_InitTypeDef pressure_GPIO_InitStructure;
  pressure_GPIO_InitStructure.GPIO_Pin = P->pin;
  pressure_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  pressure_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOC, &pressure_GPIO_InitStructure);
}

void DMA_Configure(void) {
    DMA_InitTypeDef DMA_InitStructure; 
    DMA_DeInit(DMA1_Channel1); 
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC1->DR; 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) &PRESSURE_VALUE; 
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 
    DMA_InitStructure.DMA_BufferSize = 1; 
    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; ; 
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word; 
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 
    DMA_Init(DMA1_Channel1, &DMA_InitStructure); 
    DMA_Cmd(DMA1_Channel1, ENABLE);
}

bool pressure_check(){
  return PRESSURE_VALUE >= PRESSURE_WEIGHT;
}
