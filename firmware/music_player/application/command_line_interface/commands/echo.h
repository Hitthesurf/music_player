#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/i_command.h"
#include "queue/i_char_queue.h"

namespace application
{

class Echo : public ICommand
{
public:
  Echo(threads::ICharQueue& char_output_queue);

  void Execute() const override;
  std::array<char, KeywordSize> GetKeyword() const override;

private:
  const std::array<char, KeywordSize> m_keyword = {'e', 'c', 'h', 'o', '\n'};
  threads::ICharQueue& m_char_output_queue;
};
}
