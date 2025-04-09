#include "led/led_one_driver.h"
#include "stm32h7xx_hal.h"

using namespace ::drivers;

LedOneDriver::LedOneDriver() {}

void LedOneDriver::Init() const {}

void LedOneDriver::Toggle() const
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}
