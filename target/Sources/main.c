#include "rubik_autosolver.h"
#include "relay.h"
#include "bluetooth.h"
#include "Common/utils.h"
#include <stdbool.h>

void USART1_IRQHandler() { // ��ǻ�� Ű���� �Է½�
	if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) {
		printf("Keyboard input");
	}

	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void USART2_IRQHandler() { // ������� �Է½�
	if (USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET) {
          printf("Bluetooth input");
	}

	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

int main(void) {
    struct SolverConfig config = {
        10 // dummy value
    };

    // initialize rubik cube auto solver
    init_autosolver(&config);
    
    while (get_autosolver_should_close() !=  RAS_TRUE) {
        // Do stuff
        
      GPIO_SetBits(GPIOD, GPIO_Pin_3);
      delay();
      GPIO_ResetBits(GPIOD, GPIO_Pin_3);
      delay();
    }
 
    
    
    return 0;
}
