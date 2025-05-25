#include "char_input.h"

using namespace ::application;

CharInput::CharInput(threads::ICharQueue& char_queue) :
  m_char_queue(char_queue)
{
}

void CharInput::Input(char letter)
{
  m_char_queue.AddIsr(letter);
}
