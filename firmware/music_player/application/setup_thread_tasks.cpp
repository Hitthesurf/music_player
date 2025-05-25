#include "setup_thread_tasks.h"
#include "char_input.h"
#include "char_output.h"
#include "thread_create/thread_create.h"
#include "uart/uart_driver.h"

using namespace application;
using namespace drivers;
using namespace threads;

constexpr size_t stack_size = static_cast<size_t>(2u * 1024u);

namespace
{

void CharOutputTask(uint32_t input);
ICharInput& GetCharInput();
ICharOutput& GetCharOutput();

void CharOutputTask(uint32_t input)
{
  (void)input;
  const ICharOutput& char_output = GetCharOutput();
  while (true)
  {
    char_output.RunThreadTask();
  }
}

ICharInput& GetCharInput()
{
  static std::array<uint32_t, threads::char_queue_size> queue;
  static threads::CharQueue char_queue{queue};
  static CharInput char_input{char_queue};
  return char_input;
}

ICharOutput& GetCharOutput()
{
  static ICharInput& char_input = GetCharInput();
  static UartDriver uart_driver{char_input};
  static std::array<uint32_t, threads::char_queue_size> queue_output;
  static threads::CharQueue char_queue_output{queue_output};
  static CharOutput char_output(char_queue_output, uart_driver);
  return char_output;
}

}

void SetupThreadTasks()
{
  (void)GetCharOutput(); // Need to call to init
  static std::array<uint32_t, stack_size / sizeof(uint32_t)> char_output_stack;
  static const ThreadCreate char_output_thread{char_output_stack.data(), stack_size, CharOutputTask};
}
