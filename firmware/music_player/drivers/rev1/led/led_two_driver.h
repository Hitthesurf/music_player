#include "led/i_led_driver.h"

namespace drivers
{

class LedTwoDriver : public ILedDriver
{
public:
  LedTwoDriver();
  void Init() const override;
  void Toggle() const override;
};

}
