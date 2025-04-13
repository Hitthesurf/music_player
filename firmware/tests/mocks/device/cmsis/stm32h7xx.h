#pragma once

#include "stm32h7a3xx_gpio.h"
#include "stm32h7a3xxq_st.h"
#include <cstdint>

void SET_BIT(uint32_t reg, uint32_t bit);
void CLEAR_BIT(uint32_t reg, uint32_t bit);
uint32_t READ_BIT(uint32_t reg, uint32_t bit);
void CLEAR_REG(uint32_t reg);
void WRITE_REG(uint32_t reg, uint32_t val);
uint32_t READ_REG(uint32_t reg);
void MODIFY_REG(uint32_t reg, uint32_t clearMask, uint32_t setMask);
