#include "setup_thread_tasks.h"
#include "char_output.h"
#include "thread_create/thread_create.h"
#include "uart/uart_driver.h"

using namespace application;
using namespace drivers;
using namespace threads;

// Stacks
constexpr size_t stack_size = 2 * 1024;
static uint32_t char_output_stack[stack_size / sizeof(uint32_t)];

// Tasks
static CharOutput* char_output_p;

// Task Loops
void CharOutputTask(uint32_t input);

void CharOutputTask(uint32_t input)
{
  while (true)
  {
    char_output_p->RunThreadTask();
  }
}

void SetupThreadTasks()
{
  static UartDriver uart_driver{};
  static std::array<uint32_t, threads::char_queue_size> queue;
  static threads::CharQueue char_queue{queue};
  static CharOutput char_output(char_queue, uart_driver);
  char_output_p = &char_output;

  static ThreadCreate char_output_thread{char_output_stack, stack_size, CharOutputTask};
}
