#include "i_char_output_driver.h"

namespace drivers
{

class UartDriver : public ICharOutputDriver
{
public:
  UartDriver();
  void Init() const override;
  void Output(char text) override;
};

}
