#pragma once

#include "led/i_led_driver.h"
#include "led/i_led_service.h"
#include "thread_utils.h"

namespace application
{

class LedService : public ILedService
{
public:
  LedService(drivers::ILedDriver& led_one, drivers::ILedDriver& led_two);
  void Init() const override;
  void RunTask() override;

private:
  drivers::ILedDriver& m_led_one_driver;
  drivers::ILedDriver& m_led_two_driver;
  threads::ThreadUtils m_thread_utils;
};
}
