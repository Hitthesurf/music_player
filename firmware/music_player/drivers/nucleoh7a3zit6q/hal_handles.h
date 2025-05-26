#pragma once

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim17;

void TimerAuxPwmPeriodElapsedCallback();
void TimerLoadAudioPeriodElapsedCallback();

#ifdef __cplusplus
}
#endif
