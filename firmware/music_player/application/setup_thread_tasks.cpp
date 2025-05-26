#include "setup_thread_tasks.h"
#include "char_input.h"
#include "char_output.h"
#include "command_line_interface/command_line_interface.h"
#include "command_line_interface/commands.h"
#include "command_line_interface/commands/echo.h"
#include "command_line_interface/commands/pause.h"
#include "command_line_interface/commands/play.h"
#include "hal_callbacks.h"
#include "pwm/pwm_driver.h"
#include "song_player.h"
#include "thread_create/thread_create.h"
#include "uart/uart_driver.h"

using namespace ::application;
using namespace ::application::commands;
using namespace ::drivers;
using namespace ::threads;

constexpr size_t stack_size = static_cast<size_t>(2u * 1024u);

namespace
{

void CharOutputTask(uint32_t input);
void CommandLineInterfaceTask(uint32_t input);

ICharQueue& GetCharQueueInput();
ICharQueue& GetCharQueueOutput();
ICharInput& GetCharInput();
ICharOutput& GetCharOutput();
ICommands& GetCommands();
ICommandLineInterface& GetCommandLineInterface();
ISongDriver& GetSongDriver();
ISongPlayer& GetSongPlayer();

void CharOutputTask(uint32_t input)
{
  (void)input;
  const ICharOutput& char_output = GetCharOutput();
  while (true)
  {
    char_output.RunThreadTask();
  }
}

void CommandLineInterfaceTask(uint32_t input)
{
  (void)input;
  ICommandLineInterface& command_line_interface = GetCommandLineInterface();
  while (true)
  {
    command_line_interface.RunThreadTask();
  }
}

ICharQueue& GetCharQueueInput()
{
  static std::array<uint32_t, threads::char_queue_size> queue;
  static threads::CharQueue char_queue{queue};
  return char_queue;
}

ICharQueue& GetCharQueueOutput()
{
  static std::array<uint32_t, threads::char_queue_size> queue;
  static threads::CharQueue char_queue{queue};
  return char_queue;
}

ICharInput& GetCharInput()
{
  static CharInput char_input{GetCharQueueInput()};
  return char_input;
}

ICharOutput& GetCharOutput()
{
  static UartDriver uart_driver{GetCharInput()};
  static CharOutput char_output(GetCharQueueOutput(), uart_driver);
  return char_output;
}

ICommands& GetCommands()
{
  static Echo echo{GetCharQueueOutput()};
  static Pause pause{GetSongPlayer(), GetCharQueueOutput()};
  static Play play{GetSongPlayer(), GetCharQueueOutput()};
  static const std::array<ICommand*, MaxCommandsSize> commands_array = {&echo, &pause, &play};
  constexpr size_t command_array_count = 3;
  static Commands commands{commands_array, command_array_count};
  return commands;
}

ICommandLineInterface& GetCommandLineInterface()
{
  static CommandLineInterface command_line_interface{GetCharQueueInput(), GetCommands()};
  return command_line_interface;
}

ISongDriver& GetSongDriver()
{
  static PWMDriver pwm_driver{};
  return pwm_driver;
}

ISongPlayer& GetSongPlayer()
{
  static SongPlayer song_player{GetSongDriver()};
  return song_player;
}

}

void SetupThreadTasks()
{
  // Need to call to init
  (void)GetCharOutput();
  (void)GetCommandLineInterface();

  static std::array<uint32_t, stack_size / sizeof(uint32_t)> char_output_stack;
  static const ThreadCreate char_output_thread{char_output_stack.data(), stack_size, CharOutputTask};

  static std::array<uint32_t, stack_size / sizeof(uint32_t)> command_line_interface_stack;
  static const ThreadCreate command_line_interface_thread{command_line_interface_stack.data(), stack_size,
    CommandLineInterfaceTask};

  GetSongDriver().Config(22050);
  GetSongPlayer().Play();
}

// Handle Hal callbacks
void TimerAuxPwmPeriodElapsedCallback()
{
  GetSongDriver().TimerAuxPwmPeriodElapsedCallback();
}

void TimerLoadAudioPeriodElapsedCallback()
{
  GetSongPlayer().TimerLoadAudioPeriodElapsedCallback();
}
