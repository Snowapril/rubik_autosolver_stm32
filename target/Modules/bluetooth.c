#include "bluetooth.h"
#include "Common/utils.h"

//RCC initiate for Bluetooth
static void Bluetooth_RCC_Init(){
    RCC_APB2PeriphClockCmd((RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1) , ENABLE);
    RCC_APB1PeriphClockCmd((RCC_APB1Periph_USART2) , ENABLE);
}

// GPIO initiate for Bluetooth
static void Bluetooth_GPIO_Init(){
    GPIO_InitTypeDef Gpio_Init;
    Gpio_Init.GPIO_Pin   = GPIO_Pin_2;
    Gpio_Init.GPIO_Speed = GPIO_Speed_50MHz;
    Gpio_Init.GPIO_Mode  = GPIO_Mode_AF_PP;
    
    GPIO_Init(GPIOA, &Gpio_Init);

    Gpio_Init.GPIO_Pin   = GPIO_Pin_3;
    Gpio_Init.GPIO_Speed = GPIO_Speed_50MHz;
    Gpio_Init.GPIO_Mode  = GPIO_Mode_IPD;
    
    GPIO_Init(GPIOA, &Gpio_Init);
}

static void Bluetooth_USART_Init(){
    USART_InitTypeDef Usart_Init;

    //setting for debug using the PC (USART1)
    Usart_Init.USART_BaudRate            = 115200;
    Usart_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    Usart_Init.USART_Mode                = (USART_Mode_Rx|USART_Mode_Tx);
    Usart_Init.USART_Parity              = USART_Parity_No;
    Usart_Init.USART_StopBits            = USART_StopBits_1;
    Usart_Init.USART_WordLength          = USART_WordLength_8b;
    
    USART_Init(USART1, &Usart_Init);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);

    //setting for send and receive data from bluetooth (USART2)
    Usart_Init.USART_BaudRate            = 9600;
    Usart_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    Usart_Init.USART_Mode                = (USART_Mode_Rx|USART_Mode_Tx);
    Usart_Init.USART_Parity              = USART_Parity_No;
    Usart_Init.USART_StopBits            = USART_StopBits_1;
    Usart_Init.USART_WordLength          = USART_WordLength_8b;
    
    USART_Init(USART2, &Usart_Init);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);
}

static void Bluetooth_NVIC_Init(){
    NVIC_InitTypeDef Nvic_Init;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    // PC interrupt
    Nvic_Init.NVIC_IRQChannel                   = USART1_IRQn;
    Nvic_Init.NVIC_IRQChannelPreemptionPriority = 1;
    Nvic_Init.NVIC_IRQChannelSubPriority        = 1;
    Nvic_Init.NVIC_IRQChannelCmd                = ENABLE;
    
	NVIC_Init(&Nvic_Init);

    // Bluetooth interrupt
    Nvic_Init.NVIC_IRQChannel                   = USART2_IRQn;
    Nvic_Init.NVIC_IRQChannelPreemptionPriority = 1;
    Nvic_Init.NVIC_IRQChannelSubPriority        = 1;
    Nvic_Init.NVIC_IRQChannelCmd                = ENABLE;
    
	NVIC_Init(&Nvic_Init);
}

void Bluetooth_Init(BlueConfig *config){
    config->isValid = false;
    config->isATscan = false;
    
    Bluetooth_RCC_Init();
    Bluetooth_GPIO_Init();
    Bluetooth_USART_Init();
    Bluetooth_NVIC_Init();
}


int Bluetooth_send_data(const char *data, BlueConfig *config){
    int i = 0;
    if(config->isValid == false){
		return 0; // fail for sending
	}  

	//Send data at bluetooth module

    for(i = 0; i < strlen(data); i++){
        USART_SendData(USART2, data[i]);
        delay();
    }
    
    USART_SendData(USART2, '\r');
    delay();
    
    config->isValid = false;
    return 1; // success for sending
}
