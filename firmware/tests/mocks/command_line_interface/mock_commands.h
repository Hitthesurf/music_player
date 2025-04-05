#pragma once

#include "command_line_interface/i_commands.h"
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

  application::RunCommandResult RunCommand() const override
  {
    state.run_command_call_count++;
    return state.run_command_return_value;
  }

  struct StateType
  {
    size_t init_call_count = 0;
    size_t run_command_call_count = 0;
    application::RunCommandResult run_command_return_value = application::RunCommandResult::Success;
  } mutable state{};
};

}
