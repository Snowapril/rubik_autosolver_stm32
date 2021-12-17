#include "relay.h"
#include "stm32f10x.h"

void relay_clock_enable(){
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
}

void relay_gpio_configuration(relay* R){
  relay_clock_enable();
  GPIO_InitTypeDef relay_GPIO_InitStructure;
  relay_GPIO_InitStructure.GPIO_Pin = R->pin;
  relay_GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  relay_GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &relay_GPIO_InitStructure);
}

void relay_on(relay* R){
  GPIOC->BSRR = R->set;
}

void relay_off(relay* R){
  GPIOC->BSRR = R->reset;
}
