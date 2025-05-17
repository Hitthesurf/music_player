#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/i_command.h"
#include "command_line_interface/i_commands.h"
#include "queue/i_char_queue.h"

namespace application
{

class Commands : public ICommands
{
public:
  Commands(const std::array<ICommand*, MaxCommandsSize> commands_array, size_t command_array_count);

  void Init() const override;
  RunCommandResult RunCommand(std::array<char, application::KeywordSize> keyword) const override;

private:
  const size_t m_command_array_count;
  const std::array<ICommand*, MaxCommandsSize> m_commands_array;
};
}