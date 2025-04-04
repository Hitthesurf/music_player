#pragma once

#include "command_line_interface/i_command_line_interface.h"

namespace application
{

class CommandLineInterface : public ICommandLineInterface
{
public:
  CommandLineInterface();

  void Init() const override;
  void RunThreadTask() const override;
};
}
