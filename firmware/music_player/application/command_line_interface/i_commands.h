#pragma once

#include <command_line_interface/run_command_result.h>

namespace application
{

class ICommands
{
public:
  virtual ~ICommands() = default;

  virtual void Init() const = 0;
  virtual RunCommandResult RunCommand() const = 0;
};

}
