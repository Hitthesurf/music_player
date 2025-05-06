#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/i_commands.h"
#include <array>
#include <cstddef>

namespace tests
{

class MockCommands : public application::ICommands
{
public:
  void Init() const override
  {
    state.init_call_count++;
  }

  application::RunCommandResult RunCommand(std::array<char, application::KeywordSize> keyword) const override
  {
    state.run_command_keyword = keyword;
    state.run_command_call_count++;
    return state.run_command_return_value;
  }

  struct StateType
  {
    size_t init_call_count = 0;
    size_t run_command_call_count = 0;
    std::array<char, application::KeywordSize> run_command_keyword{};
    application::RunCommandResult run_command_return_value = application::RunCommandResult::Success;
  } mutable state{};
};

}
