#pragma once

#include "led/i_led_driver.h"
#include <cstddef>

namespace tests
{

class MockLedDriver : public drivers::ILedDriver
{
public:
  void Init() const override
  {
    state.init_call_count++;
  }

  void Toggle() const override
  {
    state.toggle_call_count++;
  }

  struct StateType
  {
    size_t init_call_count = 0;
    size_t toggle_call_count = 0;
  } mutable state{};
};

}
