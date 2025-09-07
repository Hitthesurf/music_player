#include "setup_thread_tasks.h"
#include "char_input.h"
#include "char_output.h"
#include "command_line_interface/command_line_interface.h"
#include "command_line_interface/commands.h"
#include "command_line_interface/commands/echo.h"
#include "command_line_interface/commands/pause.h"
#include "command_line_interface/commands/play.h"
#include "file/secure_digital_storage.h"
#include "hal_callbacks.h"
#include "led/led_one_driver.h"
#include "led/led_service.h"
#include "led/led_two_driver.h"
#include "pwm/pwm_driver.h"
#include "read_music/read_wave.h"
#include "read_music/samples_queue.h"
#include "song_player.h"
#include "thread_create/thread_create.h"
#include "uart/uart_driver.h"

using namespace ::application;
using namespace ::application::commands;
using namespace ::drivers;
using namespace ::threads;

constexpr size_t stack_size = static_cast<size_t>(5u * 1024u);

namespace
{

void CharOutputTask(uint32_t input);
void CommandLineInterfaceTask(uint32_t input);
void LedServiceTask(uint32_t input);
void SongStreamTask(uint32_t input);

ICharQueue& GetCharQueueInput();
ICharQueue& GetCharQueueOutput();
ICharInput& GetCharInput();
ICharOutput& GetCharOutput();
ICommands& GetCommands();
ICharOutputDriver& GetUartDriver();
ICommandLineInterface& GetCommandLineInterface();
ILedService& GetLedService();
ISongDriver& GetSongDriver();
ISongPlayer& GetSongPlayer();
IReadMusic& GetReadWave();

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

void LedServiceTask(uint32_t input)
{
  (void)input;
  ILedService& led_service = GetLedService();
  while (true)
  {
    led_service.RunTask();
  }
}

void SongStreamTask(uint32_t input)
{
  (void)input;
  ISongPlayer& song_player = GetSongPlayer();
  while (true)
  {
    song_player.RunStreamThreadTask();
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

ICharOutputDriver& GetUartDriver()
{
  static UartDriver uart_driver{GetCharInput()};
  return uart_driver;
}

ICharOutput& GetCharOutput()
{
  static CharOutput char_output(GetCharQueueOutput(), GetUartDriver());
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

ILedService& GetLedService()
{
  static LedOneDriver led_one_driver;
  static LedTwoDriver led_two_driver;
  static LedService led_service{led_one_driver, led_two_driver};
  return led_service;
}

ISongDriver& GetSongDriver()
{
  static PWMDriver pwm_driver{};
  return pwm_driver;
}

IReadMusic& GetReadWave()
{
  static threads::SecureDigitalStorage sd_storage;
  static ReadWave read_wave(sd_storage);
  return read_wave;
}

ISongPlayer& GetSongPlayer()
{
  static SamplesQueue samples_queue;
  static SongPlayer song_player{GetSongDriver(), GetReadWave(), samples_queue};
  return song_player;
}

}

void SetupThreadTasks()
{
  // Need to call to init
  (void)GetCharOutput();
  (void)GetCommandLineInterface();
  GetLedService().Init();
  GetSongPlayer();

  static std::array<uint32_t, stack_size / sizeof(uint32_t)> char_output_stack;
  static const ThreadCreate char_output_thread{char_output_stack.data(), stack_size, CharOutputTask};

  static std::array<uint32_t, stack_size / sizeof(uint32_t)> command_line_interface_stack;
  static const ThreadCreate command_line_interface_thread{command_line_interface_stack.data(), stack_size,
    CommandLineInterfaceTask};

  static std::array<uint32_t, stack_size / sizeof(uint32_t)> led_service_stack;
  static const ThreadCreate led_service_thread{led_service_stack.data(), stack_size, LedServiceTask};

  static std::array<uint32_t, stack_size / sizeof(uint32_t)> song_stream_stack;
  static const ThreadCreate song_stream_thread{song_stream_stack.data(), stack_size, SongStreamTask};

  // clang-format off
  // FileName name = {'C','a','l','i','f','o','r','n','i','a',' ','(','T','h','e','r','e',' ','I','s',' ','N','o',' ','E','n','d',' ','t','o',' ','L','o','.','w','a','v'};
  // FileName name = {'C','e','d','a','r','w','o','o','d',' ','R','o','a','d','.','w','a','v'};
  // FileName name = {'C','o','l','d','p','l','a','y','V','i','v','a','L','a','V','i','d','a','.','w','a','v'};
  // FileName name = {'C','o','u','n','t',' ','O','n',' ','M','e','.','w','a','v'};
  // FileName name = {'D','a','r','k','S','t','a','r','.','w','a','v'};
  // FileName name = {'E','v','e','r','y',' ','B','r','e','a','k','i','n','g',' ','W','a','v','e','.','w','a','v'};
  // FileName name = {'G','r','e','n','a','d','e',' ','4','4','H','z',' ','S','t','e','r','o',' ','8','b','i','t','.','w','a','v'};
  // FileName name = {'H','a','l','o','3','.','w','a','v'};
  // FileName name = {'I','r','i','s',' ','(','H','o','l','d',' ','M','e',' ','C','l','o','s','e',')','.','w','a','v'};
  // FileName name = {'J','u','s','t',' ','t','h','e',' ','W','a','y',' ','Y','o','u',' ','A','r','e','.','w','a','v'};
  // FileName name = {'L','i','q','u','o','r',' ','S','t','o','r','e',' ','B','l','u','e','s',' ','(','f','e','a','t','.',' ','D','a','m','i','a','n',')','.','w','a','v'};
  // FileName name = {'M','a','r','r','y',' ','Y','o','u','.','w','a','v'};
  // FileName name = {'M','I','3','.','w','a','v'};
  // FileName name = {'O','u','r',' ','F','i','r','s','t',' ','T','i','m','e','.','w','a','v'};
  // FileName name = {'R','a','i','s','e','d',' ','B','y',' ','W','o','l','v','e','s','.','w','a','v'};
  // FileName name = {'R','u','n','a','w','a','y',' ','B','a','b','y','.','w','a','v'};
  // FileName name = {'S','l','e','e','p',' ','L','i','k','e',' ','a',' ','B','a','b','y',' ','T','o','n','i','g','h','t','.','w','a','v'};
  // FileName name = {'S','o','m','e','w','h','e','r','e',' ','I','n',' ','B','r','o','o','k','l','y','n','.','w','a','v'};
  // FileName name = {'S','o','n','g',' ','f','o','r',' ','S','o','m','e','o','n','e','.','w','a','v'};
  // FileName name = {'T','a','l','k','i','n','g',' ','t','o',' ','t','h','e',' ','M','o','o','n','.','w','a','v'};
  // FileName name = {'T','h','e',' ','L','a','z','y',' ','S','o','n','g','.','w','a','v'};
  // FileName name = {'T','h','e',' ','M','i','r','a','c','l','e',' ','(','O','f',' ','J','o','e','y',' ','R','a','m','o','n','e',')','.','w','a','v'};
  // FileName name = {'T','h','e',' ','O','t','h','e','r',' ','S','i','d','e',' ','(','f','e','a','t','.',' ','C','e','e',' ','L','o',' ','G','r','e','e',')','.','w','a','v'};
  // FileName name = {'T','h','e',' ','T','r','o','u','b','l','e','s','.','w','a','v'};
  // FileName name = {'T','h','i','s',' ','I','s',' ','W','h','e','r','e',' ','Y','o','u',' ','C','a','n',' ','R','e','a','c','h',' ','M','e',' ','N','o','.','w','a','v'};
  // FileName name = {'V','o','l','c','a','n','o','.','w','a','v'};
  FileName name = {'O','n','e','R','e','p','u','b','l','i','c','C','o','u','n','t','i','n','g','S','t','a','r','s','.','w','a','v'};
  // clang-format on
  GetSongPlayer().SelectSong(name);
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
  if (huart->Instance == USART3)
  {
    GetUartDriver().RxIsr();
  }
}
