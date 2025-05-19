#pragma once

#include "queue/i_char_queue.h"
#include <cstddef>
#include <deque>

namespace tests
{

class MockCharQueue : public threads::ICharQueue
{
public:
  void Init() const override
  {
    state.init_call_count++;
  }

  void Add(char letter) override
  {
    state.add_letter.push_back(letter);
    state.add_call_count++;
  }

  char Get() override
  {
    state.get_call_count++;
    const char value = state.get_return_value.front();
    state.get_return_value.pop_front();
    return value;
  }

  struct StateType
  {
    size_t init_call_count = 0;
    size_t add_call_count = 0;
    std::deque<char> add_letter;
    size_t get_call_count = 0;
    std::deque<char> get_return_value;
  } mutable state{};
};

}
