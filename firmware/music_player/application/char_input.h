#pragma once

#include "i_char_input.h"
#include "queue/char_queue.h"

namespace application
{

class CharInput : public ICharInput
{
public:
  explicit CharInput(threads::ICharQueue& char_queue);
  void Input(char letter) override;

private:
  threads::ICharQueue& m_char_queue;
};

}
