#include "led/led_one_driver.h"
#include "main.h"
#include "stm32h5xx_hal.h"

using namespace ::drivers;

LedOneDriver::LedOneDriver() = default;

void LedOneDriver::Init() const {}

void LedOneDriver::Toggle() const
{
  HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
}
