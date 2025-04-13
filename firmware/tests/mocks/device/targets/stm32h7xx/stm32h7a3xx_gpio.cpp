#include "stm32h7a3xx_gpio.h"

namespace
{
GPIO_TypeDef gpioa_reg;
GPIO_TypeDef gpiob_reg;
GPIO_TypeDef gpioc_reg;
GPIO_TypeDef gpiod_reg;
GPIO_TypeDef gpioe_reg;
GPIO_TypeDef gpiof_reg;
GPIO_TypeDef gpiog_reg;
GPIO_TypeDef gpioh_reg;
GPIO_TypeDef gpioi_reg;
GPIO_TypeDef gpioj_reg;
GPIO_TypeDef gpiok_reg;
}

GPIO_TypeDef* const GPIOA = &gpioa_reg;
GPIO_TypeDef* const GPIOB = &gpiob_reg;
GPIO_TypeDef* const GPIOC = &gpioc_reg;
GPIO_TypeDef* const GPIOD = &gpiod_reg;
GPIO_TypeDef* const GPIOE = &gpioe_reg;
GPIO_TypeDef* const GPIOF = &gpiof_reg;
GPIO_TypeDef* const GPIOG = &gpiog_reg;
GPIO_TypeDef* const GPIOH = &gpioh_reg;
GPIO_TypeDef* const GPIOI = &gpioi_reg;
GPIO_TypeDef* const GPIOJ = &gpioj_reg;
GPIO_TypeDef* const GPIOK = &gpiok_reg;
