#include "rubik_autosolver.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "lcd.h"
#include "system_stm32f10x.h"
#include "Common/utils.h"
#include "bluetooth.h"
#include "relay.h"
#include "action_queue.h"
#include "action.h"
#include "pressure.h"

BlueConfig* BLUETOOTH_CONFIG = NULL;
char ACTION_BUFFER[8];
int ACTION_INDEX = 0;
Queue ACTION_QUEUE;


void init_autosolver(struct SolverConfig* config) {
    // main system initialization
    SystemInit();

    // common clock enable
    RCC_APB2PeriphClockCmd(( RCC_APB2Periph_GPIOA | 
                             RCC_APB2Periph_GPIOB |
                             RCC_APB2Periph_GPIOC |
                             RCC_APB2Periph_GPIOD |
                             RCC_APB2Periph_GPIOE |
                             RCC_APB2Periph_AFIO   ), ENABLE);
    
    // initialize each modules
    // 1. init motor driver
    for (int i = 0; i < 6; ++i) {
      motor_driver_init(&config->motor_driver_configs[i]);
    }
    // 2. init bluetooth module
    Bluetooth_Init(&config->bluetooth_config);
    // 3. init relay module
    //relay relay_config = {
    //  .pin = GPIO_Pin_3,
    //  .set = GPIO_BSRR_BS8,
    //  .reset = GPIO_BSRR_BR8,
    //};
    //relay_clock_enable();
    //relay_gpio_configuration(&relay_config);
    // 4. init pressure module
    pressure_init(&config->pressure_config);
    // 5. init LCD module
    LCD_Init();
    Touch_Configuration();
    LCD_Clear(BLACK);
}

int get_autosolver_should_close() {
  return RAS_FALSE;
}

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
  
    if (received_data == '#') {
      ACTION_BUFFER[ACTION_INDEX] = '\0';
      queue_push(&ACTION_QUEUE, ACTION_BUFFER);
      printf("pushed : %s\n", ACTION_BUFFER);
      ACTION_INDEX = 0;
    } else {
      ACTION_BUFFER[ACTION_INDEX++] = received_data;
    }
    printf("received : %c\n", received_data);
    USART_SendData(USART1, received_data); // Send to USART2(bluetooth)

    if (BLUETOOTH_CONFIG)
      BLUETOOTH_CONFIG->isValid = true;

    USART_ClearITPendingBit(USART2, USART_IT_RXNE); // USART2 PendingBit Clear
}

void loop(struct SolverConfig* config) {
  static char* ACTION_TABLE[6][2] = {
    { "L", "Li" },
    { "R", "Ri" },
    { "U", "Ui" },
    { "D", "Di" },
    { "F", "Fi" },
    { "B", "Bi" },
  };
  
  if (BLUETOOTH_CONFIG) {
    if (!BLUETOOTH_CONFIG->isATscan && Bluetooth_send_data("AT+BTSCAN", BLUETOOTH_CONFIG)) {
      BLUETOOTH_CONFIG->isATscan = true;
      delay_ms(250);
    }
    if (BLUETOOTH_CONFIG->isATscan) {
      BLUETOOTH_CONFIG->isValid = true;
      // Bluetooth_send_Data("true", BLUETOOTH_CONFIG); pressure module
    }                                                       
  }
  
  // Check cube attached
  if (pressure_check()) {
    printf("Cube attached!! \n");
    Bluetooth_send_data("@", BLUETOOTH_CONFIG);
  }
  
  LCD_ShowString(10, 120, "PNU Embedded Term Project", WHITE, BLACK);
  LCD_ShowString(10, 170, "Next Action : ", WHITE, BLACK);
  if (isEmpty(&ACTION_QUEUE) == false) {
    enum ActionType type;
    queue_pop(&ACTION_QUEUE, &type);
    if (type == ACTION_UNDEFINED) return;
    int index, clockwise;
    query_action(type, &index, &clockwise);
    printf("Action(%s), index(%d), clockwise(%d)\n", ACTION_TABLE[index][clockwise], index, clockwise);
    LCD_ShowString(120, 170, ACTION_TABLE[index][clockwise], WHITE, BLACK);
    motor_driver_rotate(&config->motor_driver_configs[index],
                        MOTOR_QUARTER_ANGLE, MOTOR_SPEED, clockwise);
    delay_ms(100);
    LCD_Clear(BLACK);
  } else {
    LCD_ShowString(120, 170, "No action", WHITE, BLACK);
  }
}

