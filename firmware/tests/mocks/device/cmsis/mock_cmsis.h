#pragma once

#include "stm32h7a3xx_gpio.h"
#include "stm32h7a3xxq_st.h"
#include <cstddef>
#include <cstdint>

void ResetCMSIS();

struct State_SET_BIT
{
  size_t call_count = 0;
  uint32_t reg;
  uint32_t bit;
};

struct State_CLEAR_BIT
{
  size_t call_count = 0;
  uint32_t reg;
  uint32_t bit;
};

struct State_READ_BIT
{
  size_t call_count = 0;
  uint32_t reg;
  uint32_t bit;
  uint32_t return_value;
};

struct State_CLEAR_REG
{
  size_t call_count = 0;
  uint32_t reg;
};

struct State_WRITE_REG
{
  size_t call_count = 0;
  uint32_t reg;
  uint32_t val;
};

struct State_READ_REG
{
  size_t call_count = 0;
  uint32_t reg;
  uint32_t return_value;
};

struct State_MODIFY_REG
{
  size_t call_count = 0;
  uint32_t reg;
  uint32_t clearMask;
  uint32_t setMask;
};

extern State_SET_BIT state_SET_BIT;
extern State_CLEAR_BIT state_CLEAR_BIT;
extern State_READ_BIT state_READ_BIT;
extern State_CLEAR_REG state_CLEAR_REG;
extern State_WRITE_REG state_WRITE_REG;
extern State_READ_REG state_READ_REG;
extern State_MODIFY_REG state_MODIFY_REG;
