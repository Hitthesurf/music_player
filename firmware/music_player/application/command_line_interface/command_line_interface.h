#pragma once

#include "command_line_interface/i_command_line_interface.h"
#include "command_line_interface/i_commands.h"
#include "queue/i_char_queue.h"

namespace application
{

class CommandLineInterface : public ICommandLineInterface
{
public:
  CommandLineInterface(threads::ICharQueue& char_queue, ICommands& commands);

  void Init() const override;
  void RunThreadTask() const override;

private:
  threads::ICharQueue& m_char_queue;
  ICommands& m_commands;
};
}
