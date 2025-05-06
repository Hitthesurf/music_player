#include "command_line_interface/command_line_interface.h"
#include "command_line_interface/mock_commands.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::tests;

class CommandLineInterfaceTests : public testing::Test
{
public:
  CommandLineInterfaceTests() :
    m_command_line_interface(m_char_queue, m_commands)
  {
  }

protected:
  MockCharQueue m_char_queue{};
  MockCommands m_commands{};
  CommandLineInterface m_command_line_interface;
};

TEST_F(CommandLineInterfaceTests, calls_run_command_when_a_newline_is_recieved)
{
  // Given
  std::string text = "test\n";
  for (size_t i = 0; i < text.length(); i++)
  {
    m_char_queue.state.get_return_value.push_back(text[i]);
  }

  // When
  for (size_t i = 0; i < text.length(); i++)
  {
    m_command_line_interface.RunThreadTask();
  }

  // Then
  ASSERT_EQ(1, m_commands.state.run_command_call_count);
  ASSERT_EQ(memcmp(text.data(), m_commands.state.run_command_keyword.data(), text.size()), 0);
}

TEST_F(CommandLineInterfaceTests, does_not_call_run_command_when_a_newline_is_not_recieved)
{
  // Given
  std::string text = "test";
  for (size_t i = 0; i < text.length(); i++)
  {
    m_char_queue.state.get_return_value.push_back(text[i]);
  }

  // When
  for (size_t i = 0; i < text.length(); i++)
  {
    m_command_line_interface.RunThreadTask();
  }

  // Then
  ASSERT_EQ(0, m_commands.state.run_command_call_count);
}
