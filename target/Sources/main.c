#include "rubik_autosolver.h"
#include "relay.h"
#include "bluetooth.h"
#include "motor_driver.h"
#include "Common/utils.h"
#include "action_queue.h"
#include <stdbool.h>

extern BlueConfig* BLUETOOTH_CONFIG;
extern Queue ACTION_QUEUE;

static struct SolverConfig default_app_config() {
  static struct SolverConfig config = {
    .bluetooth_config = { .isValid = false, .isATscan = false },
    .motor_driver_configs = {
      // Left Face
      { .step_port=GPIOB, .step_pin=GPIO_Pin_12,
        .enable_port=GPIOB, .enable_pin=GPIO_Pin_14, 
        .dir_port=GPIOD, .dir_pin=GPIO_Pin_8 },
      // Right Face
      { .step_port=GPIOD, .step_pin=GPIO_Pin_10,
        .enable_port=GPIOD, .enable_pin=GPIO_Pin_12, 
        .dir_port=GPIOD, .dir_pin=GPIO_Pin_14 },
      // Up Face
      { .step_port=GPIOC, .step_pin=GPIO_Pin_6,
        .enable_port=GPIOC, .enable_pin=GPIO_Pin_8, 
        .dir_port=GPIOA, .dir_pin=GPIO_Pin_8 },
      // Down Face
      { .step_port=GPIOA, .step_pin=GPIO_Pin_10,
        .enable_port=GPIOA, .enable_pin=GPIO_Pin_12, 
        .dir_port=GPIOA, .dir_pin=GPIO_Pin_14 },
      // Front Face
      { .step_port=GPIOC, .step_pin=GPIO_Pin_10,
        .enable_port=GPIOC, .enable_pin=GPIO_Pin_12, 
        .dir_port=GPIOD, .dir_pin=GPIO_Pin_1 },
      // Back Face
      { .step_port=GPIOD, .step_pin=GPIO_Pin_3,
        .enable_port=GPIOD, .enable_pin=GPIO_Pin_5, 
        .dir_port=GPIOD, .dir_pin=GPIO_Pin_7 },
    },
    .pressure_config = { .port = GPIOC, .pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 },
  };
  return config;
}

int main(void) {
    struct SolverConfig config = default_app_config();
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
