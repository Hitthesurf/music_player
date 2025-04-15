#pragma once

#include "led/i_led_service.h"

namespace application
{

class App
{
public:
  explicit App(ILedService& led_service);
  void Init();
  void Run();

private:
  ILedService& m_led_service;
};
}
