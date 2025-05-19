#pragma once

#include "i_char_output_driver.h"
#include <cstddef>
#include <deque>

namespace tests
{

class MockCharOutputDriver : public drivers::ICharOutputDriver
{
public:
  void Init() const override
  {
    state.init_call_count++;
  }

  void Output(char text) const override
  {
    state.output_call_count++;
    state.output_text.push_back(text);
  }

  struct StateType
  {
    size_t init_call_count = 0;
    size_t output_call_count = 0;
    std::deque<char> output_text;
  } mutable state{};
};

}
