#include "led/led_two_driver.h"
#include "stm32h7xx.h"

using namespace ::drivers;

LedTwoDriver::LedTwoDriver() {}

// PB0
void LedTwoDriver::Init() const
{
  // Enable PB IO clock
  SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN);

  // Note: Need some NO Ops

  // Set PB0 to no pull-up, pull-down
  CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPD0);

  // Set PB0 to output push-pull
  CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT0);

  // Set PB0 output speed to low
  CLEAR_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED0);

  // Set PB0 to general purpose output mode
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0, GPIO_MODER_MODE0_0);
}

void LedTwoDriver::Toggle() const
{
  const uint32_t bit_value = READ_BIT(GPIOB->ODR, GPIO_ODR_OD0);
  const bool bit_set = (GPIO_ODR_OD0 == bit_value);

  const uint32_t bit_to_set = bit_set ? GPIO_BSRR_BR0 : GPIO_BSRR_BS0;
  SET_BIT(GPIOB->BSRR, bit_to_set);
}
