#pragma once

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;

void TimerAuxPwmPeriodElapsedCallback();

#ifdef __cplusplus
}
#endif
