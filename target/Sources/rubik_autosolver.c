#include "rubik_autosolver.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "system_stm32f10x.h"
#include "bluetooth.h"
#include "relay.h"
#include "pressure.h"

void init_autosolver(struct SolverConfig* config) {
    // main system initialization
    SystemInit();

    // common clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    
    // initialize each modules
    // 1. init motor driver
    motor_driver_init(&config->motor_driver_config);
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
}

int get_autosolver_should_close() {
  return RAS_FALSE;
}
