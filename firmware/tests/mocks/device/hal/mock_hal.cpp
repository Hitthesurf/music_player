#include "mock_hal.h"

// NOLINTBEGIN
State_HAL_GPIO_TogglePin state_HAL_GPIO_TogglePin;

void ResetHAL()
{
  state_HAL_GPIO_TogglePin.call_count = 0;
}

void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  state_HAL_GPIO_TogglePin.call_count++;
  state_HAL_GPIO_TogglePin.GPIOx = GPIOx;
  state_HAL_GPIO_TogglePin.GPIO_Pin = GPIO_Pin;
}

// NOLINTEND
