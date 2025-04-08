#include "led/led_service.h"

using namespace ::application;
using namespace ::drivers;

LedService::LedService(ILedDriver& led_driver) :
  m_led_driver(led_driver)
{
}

void LedService::Init() const
{
  m_led_driver.Init();
}

void LedService::RunTask() const
{
  m_led_driver.Toggle();
}
