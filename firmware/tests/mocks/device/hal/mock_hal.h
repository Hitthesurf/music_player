#pragma once

#include "stm32h7xx_hal.h"
#include <cstddef>

void ResetHAL();

struct State_HAL_GPIO_TogglePin
{
  size_t call_count = 0;
  GPIO_TypeDef* GPIOx;
  uint16_t GPIO_Pin;
};

extern State_HAL_GPIO_TogglePin state_HAL_GPIO_TogglePin;
