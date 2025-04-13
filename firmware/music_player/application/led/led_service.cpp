#include "led/led_service.h"

using namespace ::application;
using namespace ::drivers;

LedService::LedService(ILedDriver& led_one_driver, ILedDriver& led_two_driver) :
  m_led_one_driver(led_one_driver),
  m_led_two_driver(led_two_driver)
{
}

void LedService::Init() const
{
  m_led_one_driver.Init();
  m_led_two_driver.Init();
}

void LedService::RunTask() const
{
  m_led_one_driver.Toggle();
  m_led_two_driver.Toggle();
}
