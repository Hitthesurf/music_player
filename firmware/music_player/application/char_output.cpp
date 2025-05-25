#include "char_output.h"
#include <cstring>

using namespace ::application;

CharOutput::CharOutput(threads::ICharQueue& char_queue, drivers::ICharOutputDriver& char_output_driver) :
  m_char_queue(char_queue),
  m_char_output_driver(char_output_driver)
{
}

void CharOutput::Init() const {}

void CharOutput::RunThreadTask() const
{
  static bool first_time = true;
  if (first_time)
  {
    Output("Hello World\n");
    first_time = false;
  }
  const char letter = m_char_queue.Get();
  m_char_output_driver.Output(letter);
}

void CharOutput::Output(const char* text) const
{
  for (size_t i = 0; i < strlen(text); i++)
  {
    m_char_queue.Add(text[i]);
  }
}
