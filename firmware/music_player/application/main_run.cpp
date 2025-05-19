#include "main_run.h"
#include "app.h"
#include "led/led_one_driver.h"
#include "led/led_service.h"
#include "led/led_two_driver.h"

#include "queue/char_queue.h"

using namespace ::application;
using namespace ::drivers;

void MainRun()
{

  LedOneDriver led_one_driver;
  LedTwoDriver led_two_driver;
  LedService led_service(led_one_driver, led_two_driver);
  App my_app(led_service);
  my_app.Init();

  std::array<uint32_t, threads::char_queue_size> queue;
  threads::CharQueue char_queue{queue};

  while (true)
  {
    char_queue.Add('h');
    my_app.Run();
    if (char_queue.Get() != 'h')
    {
      break;
    }
  }
}
