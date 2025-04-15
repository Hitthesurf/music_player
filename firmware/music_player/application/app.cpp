#include "app.h"
#include "stm32h7xx_hal.h"

using namespace ::application;

App::App(ILedService& led_service) :
  m_led_service(led_service)
{
}

void App::Init()
{
  m_led_service.Init();
}

void App::Run()
{
  m_led_service.RunTask();
  HAL_Delay(500);
}
