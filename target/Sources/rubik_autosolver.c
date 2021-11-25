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