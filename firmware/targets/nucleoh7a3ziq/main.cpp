#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include <stddef.h>

static inline void NO_OP()
{
  __asm__ __volatile__("nop");
}

void wait()
{
  for (size_t i = 0; i < 1000000; i++)
  {
    NO_OP();
  }
}

int main()
{

  // Enable PA IO clock
  SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOBEN);

  // Set PA6 to general purpose output mode
  MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE0, GPIO_MODER_MODE0_0);

  // Setup red LED using HAL PB14
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  while (true)
  {
    // Toggle Other LED
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);

    // Toggle User LED
    const uint32_t bit_value = READ_BIT(GPIOB->ODR, GPIO_ODR_OD0);
    const bool bit_set = (bit_value == GPIO_ODR_OD0);

    const uint32_t bsr = bit_set ? GPIO_BSRR_BR0 : GPIO_BSRR_BS0;

    SET_BIT(GPIOB->BSRR, bsr);
    wait();
  }
}
