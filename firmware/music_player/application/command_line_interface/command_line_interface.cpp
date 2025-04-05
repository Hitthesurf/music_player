#include "command_line_interface/command_line_interface.h"

using namespace ::application;
using namespace ::threads;

CommandLineInterface::CommandLineInterface(ICharQueue& char_queue, ICommands& commands) :
  m_char_queue(char_queue),
  m_commands(commands)
{
}

void CommandLineInterface::Init() const {}

void CommandLineInterface::RunThreadTask() const
{
  if (m_char_queue.Get() == '\n')
  {
    m_commands.RunCommand();
  }
}
