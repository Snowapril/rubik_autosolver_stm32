#include "rubik_autosolver.h"
#include "relay.h"
#include "bluetooth.h"
#include "Common/utils.h"
#include <stdbool.h>

BlueConfig blue;

/// IRQHandler Setting
void USART1_IRQHandler(){
    unsigned char recvbuf = '\0';

    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ; // Wait the USART1 Tx to SET
    recvbuf = (unsigned char)USART_ReceiveData(USART1);
    USART_SendData(USART1, recvbuf); // ECHO
    USART_SendData(USART2, recvbuf); // Send to bluetooth

    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void USART2_IRQHandler(){
    unsigned char recvbuf = '\0';

    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
        ; // Wait the USART2 Tx to SET
    recvbuf = (unsigned char)USART_ReceiveData(USART2); // ECHO
    USART_SendData(USART1, recvbuf); // Send to bluetooth

    blue.isValid = true;

    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

int main(void) {
    struct SolverConfig config = {
        10 // dummy value
    };

    // initialize rubik cube auto solver
    init_autosolver(&config);
    
    Bluetooth_Init(&blue);
    if(!blue.isATscan && Bluetooth_send_data("AT+BTSCAN", &blue)){
        blue.isATscan = true;
        delay();
    }

    while (get_autosolver_should_close() !=  RAS_TRUE) {
        // Do stuff
    }
    
    return 0;
}
