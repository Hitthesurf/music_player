#pragma once

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

void TimerAuxPwmPeriodElapsedCallback();
void TimerLoadAudioPeriodElapsedCallback();

#ifdef __cplusplus
}
#endif
