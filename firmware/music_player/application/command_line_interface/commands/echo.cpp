#include "command_line_interface/commands/echo.h"

using namespace ::application;
using namespace ::threads;

Echo::Echo(threads::ICharQueue& char_output_queue) :
  m_char_output_queue(char_output_queue)
{
}

void Echo::Execute() const
{
  m_char_output_queue.Add('E');
  m_char_output_queue.Add('c');
  m_char_output_queue.Add('h');
  m_char_output_queue.Add('o');
  m_char_output_queue.Add('\n');
}

std::array<char, KeywordSize> Echo::GetKeyword() const
{
  return m_keyword;
}
