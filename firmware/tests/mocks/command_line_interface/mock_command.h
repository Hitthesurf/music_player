#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/i_command.h"
#include <array>
#include <cstddef>

namespace tests
{

class MockCommand : public application::ICommand
{
public:
  void Execute() const override
  {
    state.execute_call_count++;
  }

  std::array<char, application::KeywordSize> GetKeyword() const override
  {
    state.get_keyword_call_count++;
    return state.get_keyword_keyword;
  }

  struct StateType
  {
    size_t execute_call_count = 0;
    size_t get_keyword_call_count = 0;
    std::array<char, application::KeywordSize> get_keyword_keyword{};
  } mutable state{};
};

}
