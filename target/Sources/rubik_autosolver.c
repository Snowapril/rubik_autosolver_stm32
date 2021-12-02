#include "rubik_autosolver.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "system_stm32f10x.h"

void init_autosolver(struct SolverConfig* config) {
    // main system initialization
    SystemInit();

    // common clock enable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

int get_autosolver_should_close() {
  return RAS_FALSE;
}

struct MotorDriverConfig get_motor_default_config() {
  return struct MotorDriverConfig {
    .gpio_clock_port = RCC_APB2Periph_GPIOD,
    .common_gpio_port = GPIOD,
    .step_pin = GPIO_PIN_3,
    .enable_pin = GPIO_PIN_4,
    .dir_pin = GPIO_PIN5,
    .timer_clock_port = RCC_APB1Periph_TIM4,
    .timer_pin = TIM4,
  };
}
