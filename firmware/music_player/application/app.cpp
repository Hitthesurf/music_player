#include "app.h"
#include "stm32h7xx_hal.h"

void Run()
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
  HAL_Delay(500);
}
