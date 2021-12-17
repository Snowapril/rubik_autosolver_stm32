#include "rubik_autosolver.h"
#include "relay.h"
#include "bluetooth.h"
#include "motor_driver.h"
#include "Common/utils.h"
#include <stdbool.h>

extern BlueConfig bluetooth_config;

void USART1_IRQHandler(){
    char received_data = '\0'; //for save data

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // Wait the USART1 Tx to SET
    
    received_data = USART_ReceiveData(USART1) & 0xFF; //saving received data

    USART_SendData(USART1, received_data); // Send to USART1
    USART_SendData(USART2, received_data); // Send to USART2(bluetooth)

    USART_ClearITPendingBit(USART1, USART_IT_RXNE); // USART1 PendingBit Clear
}

void USART2_IRQHandler(){
    char received_data = '\0'; //for save data

    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait the USART2 Tx to SET
    
    received_data = (unsigned char)USART_ReceiveData(USART2) & 0xFF; //saving received data

    USART_SendData(USART1, received_data); // Send to USART2(bluetooth)

    // blue.isValid = true;

    USART_ClearITPendingBit(USART2, USART_IT_RXNE); // USART2 PendingBit Clear
}

// <  Bluetooth Config  >
//  isATscan : false
//  isValid : false
static BlueConfig get_bluetooth_default_config() {
   static BlueConfig config = {
    .isValid= false,
    .isATscan = false,
  };
  return config;
}

// <  Motor Driver Config  >
//  GPIO Clock  : APB2_GPIOD
//  Common GPIO : GPIOD
//  Step Pin    : Pin 3
//  Enable Pin  : Pin 4
//  Dir Pin     : Pin 5
//  Timer Clock : APB1_TIM4
//  Timer Pin   : TIM4
static struct MotorDriverConfig get_motor_default_config() {
   static struct MotorDriverConfig config = {
    .gpio_clock_port = RCC_APB2Periph_GPIOD,
    .common_gpio_port = GPIOD,
    .step_pin = GPIO_Pin_3,
    .enable_pin = GPIO_Pin_4,
    .dir_pin = GPIO_Pin_5,
    .timer_clock_port = RCC_APB1Periph_TIM4,
    .timer_pin = TIM4,
  };
  return config;
}

int main(void) {
    struct SolverConfig config = {
        .bluetooth_config = get_bluetooth_default_config(),
        .motor_driver_config = get_motor_default_config(),
    };

    // initialize rubik cube auto solver
    init_autosolver(&config);
    
    while (get_autosolver_should_close() !=  RAS_TRUE) {
        // Do stuff
      //if (!config.bluetooth_config.isATscan && Bluetooth_send_data("AT+BTSCAN", &config.bluetooth_config)) {
      //  config.bluetooth_config.isATscan = true;
      //  delay_ms(250);
      //}
    }
 
    return 0;
}
