#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/run_command_result.h"
#include <array>

namespace application
{

class ICommands
{
public:
  virtual ~ICommands() = default;

  virtual void Init() const = 0;
  virtual RunCommandResult RunCommand(std::array<char, application::KeywordSize> keyword) const = 0;
};

}
