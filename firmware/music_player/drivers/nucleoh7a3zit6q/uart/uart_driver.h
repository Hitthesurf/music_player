#include "i_char_input.h"
#include "i_char_output_driver.h"
#include <cstdint>

namespace drivers
{

class UartDriver : public ICharOutputDriver
{
public:
  UartDriver(application::ICharInput& char_input);
  void Init() const override;
  void Output(char text) override;
  void RxIsr();

private:
  application::ICharInput& m_char_input;
  uint8_t m_rx_byte = 0;
};

}
