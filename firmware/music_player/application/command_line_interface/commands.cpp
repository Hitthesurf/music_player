#include "command_line_interface/commands.h"
#include <cstring>

using namespace ::application;

Commands::Commands(const std::array<ICommand*, MaxCommandsSize> commands_array, size_t command_array_count) :
  m_commands_array(commands_array),
  m_command_array_count(command_array_count)
{
}

RunCommandResult Commands::RunCommand(std::array<char, application::KeywordSize> keyword) const
{
  const size_t keyword_valid_size = GetKeywordValidSize(keyword);
  if (keyword_valid_size == 0)
  {
    return RunCommandResult::NoCommandFound;
  }

  for (size_t i = 0; i < m_command_array_count; i++)
  {
    if (memcmp(m_commands_array.at(i)->GetKeyword().data(), keyword.data(), keyword_valid_size) == 0)
    {
      m_commands_array.at(i)->Execute();
      return RunCommandResult::CommandFound;
    }
  }
  return RunCommandResult::NoCommandFound;
}

size_t Commands::GetKeywordValidSize(const std::array<char, application::KeywordSize>& keyword) const
{
  for (size_t i = 0; i < keyword.size(); ++i)
  {
    if (keyword.at(i) == '\n')
    {
      return i + 1; // Include the '\n' in the valid size
    }
  }
  return 0; // '\n' not found — keyword invalid or incomplete
}
