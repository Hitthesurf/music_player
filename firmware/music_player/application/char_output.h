#pragma once

#include "i_char_output.h"
#include "i_char_output_driver.h"
#include "queue/char_queue.h"

namespace application
{

class CharOutput : public ICharOutput
{
public:
  CharOutput(threads::ICharQueue& char_queue, drivers::ICharOutputDriver& char_output_driver);

  void Init() const override;
  void RunThreadTask() const override;
  void Output(const char* text) const override;

private:
  threads::ICharQueue& m_char_queue;
  drivers::ICharOutputDriver& m_char_output_driver;
};

}
