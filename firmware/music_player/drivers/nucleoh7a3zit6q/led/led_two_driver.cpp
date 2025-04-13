#include "led/led_two_driver.h"
#include "stm32h7xx.h"

using namespace ::drivers;

LedTwoDriver::LedTwoDriver() {}

// PB0
void LedTwoDriver::Init() const {}

void LedTwoDriver::Toggle() const
{
  const uint32_t bit_value = READ_BIT(GPIOB->ODR, GPIO_ODR_OD0);
  const bool bit_set = (GPIO_ODR_OD0 == bit_value);

  const uint32_t bit_to_set = bit_set ? GPIO_BSRR_BR0 : GPIO_BSRR_BS0;
  SET_BIT(GPIOB->BSRR, bit_to_set);
}
