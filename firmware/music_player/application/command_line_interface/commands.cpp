#include "command_line_interface/commands.h"

using namespace ::application;

Commands::Commands(const std::array<ICommand*, MaxCommandsSize> commands_array, size_t command_array_count) :
  m_commands_array(commands_array),
  m_command_array_count(command_array_count)
{
}

void Commands::Init() const {}

RunCommandResult Commands::RunCommand(std::array<char, application::KeywordSize> keyword) const
{
  for (size_t i = 0; i < m_command_array_count; i++)
  {
    m_commands_array.at(i)->GetKeyword();
  }
  return RunCommandResult::NoCommandFound;
}
