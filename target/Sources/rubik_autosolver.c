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
    //struct MotorDriverConfig motor_config = get_motor_default_config();
    //motor_driver_init(&motor_config);
    // 2. init bluetooth module
    BlueConfig blue_config;
    Bluetooth_Init(&blue_config);
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
