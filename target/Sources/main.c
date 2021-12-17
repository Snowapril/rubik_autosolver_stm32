#include "rubik_autosolver.h"
#include "relay.h"
#include "bluetooth.h"
#include "motor_driver.h"
#include "Common/utils.h"
#include <stdbool.h>

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

int main(void) {
    struct SolverConfig config = {
        .bluetooth_config = get_bluetooth_default_config(),
        .motor_driver_configs = {
          get_motor1_default_config(),
          get_motor1_default_config(),
          get_motor1_default_config(),
          get_motor1_default_config(),
          get_motor1_default_config(),
          get_motor1_default_config(),
        },
    };

    // initialize rubik cube auto solver
    
    unsigned int steps = 200, motor_delay = 100;
    while (get_autosolver_should_close() !=  RAS_TRUE) {
        // Do stuff
      for (int i = 0; i < steps; i++) {
        GPIO_SetBits(config.motor_driver_configs[0].common_gpio_port,
                     config.motor_driver_configs[0].step_pin);
        delay_ms(motor_delay);
        GPIO_ResetBits(config.motor_driver_configs[0].common_gpio_port,
                     config.motor_driver_configs[0].step_pin);
        delay_ms(motor_delay);
      }
    }
 
    return 0;
}
