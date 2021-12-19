#include "rubik_autosolver.h"
#include "relay.h"
#include "bluetooth.h"
#include "motor_driver.h"
#include "Common/utils.h"
#include "action_queue.h"
#include <stdbool.h>

extern BlueConfig* BLUETOOTH_CONFIG;
extern Queue ACTION_QUEUE;

static struct SolverConfig defaultAppConfig() {
  static struct SolverConfig config = {
    .bluetooth_config = { .isValid = false, .isATscan = false },
    .motor_driver_configs = {
      { .gpio_clock_port=RCC_APB2Periph_GPIOD, .common_gpio_port=GPIOD,
        .step_pin=GPIO_Pin_3, .enable_pin=GPIO_Pin_4, .dir_pin=GPIO_Pin_5 },
      { .gpio_clock_port=RCC_APB2Periph_GPIOD, .common_gpio_port=GPIOD,
        .step_pin=GPIO_Pin_6, .enable_pin=GPIO_Pin_7, .dir_pin=GPIO_Pin_8 },
      { .gpio_clock_port=RCC_APB2Periph_GPIOD, .common_gpio_port=GPIOD,
        .step_pin=GPIO_Pin_9, .enable_pin=GPIO_Pin_10, .dir_pin=GPIO_Pin_11 },
      { .gpio_clock_port=RCC_APB2Periph_GPIOD, .common_gpio_port=GPIOD,
        .step_pin=GPIO_Pin_12, .enable_pin=GPIO_Pin_13, .dir_pin=GPIO_Pin_14 },
      { .gpio_clock_port=RCC_APB2Periph_GPIOE, .common_gpio_port=GPIOE,
        .step_pin=GPIO_Pin_3, .enable_pin=GPIO_Pin_4, .dir_pin=GPIO_Pin_5 },
      { .gpio_clock_port=RCC_APB2Periph_GPIOE, .common_gpio_port=GPIOE,
        .step_pin=GPIO_Pin_6, .enable_pin=GPIO_Pin_7, .dir_pin=GPIO_Pin_8 },
    },
  };
  return config;
}

int main(void) {
    struct SolverConfig config = defaultAppConfig();
    BLUETOOTH_CONFIG = &config.bluetooth_config;
    queue_init(&ACTION_QUEUE);
    // Initialize rubik auto solver application
    init_autosolver(&config);
    
    // Main loop for this application
    while (get_autosolver_should_close() !=  RAS_TRUE) {
        loop(&config);
    }
 
    return 0;
}
