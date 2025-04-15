#include "mock_cmsis.h"
#include "stm32h7xx.h"

State_SET_BIT state_SET_BIT;
State_CLEAR_BIT state_CLEAR_BIT;
State_READ_BIT state_READ_BIT;
State_CLEAR_REG state_CLEAR_REG;
State_WRITE_REG state_WRITE_REG;
State_READ_REG state_READ_REG;
State_MODIFY_REG state_MODIFY_REG;

void ResetCMSIS()
{
  state_SET_BIT.call_count = 0;
  state_CLEAR_BIT.call_count = 0;
  state_READ_BIT.call_count = 0;
  state_CLEAR_REG.call_count = 0;
  state_WRITE_REG.call_count = 0;
  state_READ_REG.call_count = 0;
  state_MODIFY_REG.call_count = 0;
}

void SET_BIT(uint32_t reg, uint32_t bit)
{
  state_SET_BIT.call_count++;
  state_SET_BIT.reg = reg;
  state_SET_BIT.bit = bit;
}

void CLEAR_BIT(uint32_t reg, uint32_t bit)
{
  state_CLEAR_BIT.call_count++;
  state_CLEAR_BIT.reg = reg;
  state_CLEAR_BIT.bit = bit;
}

uint32_t READ_BIT(uint32_t reg, uint32_t bit)
{
  state_READ_BIT.call_count++;
  state_READ_BIT.reg = reg;
  state_READ_BIT.bit = bit;
  return state_READ_BIT.return_value;
}

void CLEAR_REG(uint32_t reg)
{
  state_CLEAR_REG.call_count++;
  state_CLEAR_REG.reg = reg;
}

void WRITE_REG(uint32_t reg, uint32_t val)
{
  state_WRITE_REG.call_count++;
  state_WRITE_REG.reg = reg;
  state_WRITE_REG.val = val;
}

uint32_t READ_REG(uint32_t reg)
{
  state_READ_REG.call_count++;
  state_READ_REG.reg = reg;
  return state_READ_REG.return_value;
}

void MODIFY_REG(uint32_t reg, uint32_t clear_mask, uint32_t set_mask)
{
  state_MODIFY_REG.call_count++;
  state_MODIFY_REG.reg = reg;
  state_MODIFY_REG.clear_mask = clear_mask;
  state_MODIFY_REG.set_mask = set_mask;
}
