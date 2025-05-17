#include "command_line_interface/command_line_interface.h"

using namespace ::application;
using namespace ::threads;

CommandLineInterface::CommandLineInterface(ICharQueue& char_queue, ICommands& commands) :
  m_char_queue(char_queue),
  m_commands(commands)
{
}

void CommandLineInterface::Init() const {}

void CommandLineInterface::RunThreadTask()
{
  const char letter = m_char_queue.Get();
  m_working_buffer.at(m_working_buffer_valid_items) = letter;
  m_working_buffer_valid_items++;
  if (letter == '\n')
  {
    m_commands.RunCommand(m_working_buffer);
    m_working_buffer_valid_items = 0;
  }
  if (m_working_buffer_valid_items == KeywordSize)
  {
    m_working_buffer_valid_items = 0;
  }
}
