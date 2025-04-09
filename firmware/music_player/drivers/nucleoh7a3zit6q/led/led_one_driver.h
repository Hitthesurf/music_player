#include "led/i_led_driver.h"

namespace drivers
{

class LedOneDriver : public ILedDriver
{
public:
  LedOneDriver();
  void Init() const override;
  void Toggle() const override;
};

}
