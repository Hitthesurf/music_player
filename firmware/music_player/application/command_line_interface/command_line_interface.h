#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/i_command_line_interface.h"
#include "command_line_interface/i_commands.h"
#include "queue/i_char_queue.h"

namespace application
{

class CommandLineInterface : public ICommandLineInterface
{
public:
  CommandLineInterface(threads::ICharQueue& char_queue, ICommands& commands);

  void Init() const override {};
  void RunThreadTask() override;

private:
  size_t m_working_buffer_valid_items = 0;
  std::array<char, application::KeywordSize> m_working_buffer{};
  threads::ICharQueue& m_char_queue;
  ICommands& m_commands;
};
}
