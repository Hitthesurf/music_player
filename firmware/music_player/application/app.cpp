#include "app.h"
#include "led/led_one_driver.h"
#include "led/led_service.h"
#include "led/led_two_driver.h"
#include "stm32h7xx_hal.h"

using namespace ::application;
using namespace ::drivers;

static LedOneDriver led_one_driver;
static LedTwoDriver led_two_driver;
static LedService led_service(led_one_driver, led_two_driver);

void AppInit()
{
  led_service.Init();
}

void AppRun()
{
  led_service.RunTask();
  HAL_Delay(500);
}
