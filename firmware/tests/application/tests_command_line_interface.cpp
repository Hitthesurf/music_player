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

TEST_F(CommandLineInterfaceTests, calls_run_command_when_a_newline_is_recieved_1)
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

TEST_F(CommandLineInterfaceTests, calls_run_command_when_a_newline_is_recieved_2)
{
  // Given
  std::string text = "other_command\n";
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

TEST_F(CommandLineInterfaceTests, calls_run_command_twice_when_two_commands_recieved)
{
  // Given
  std::string text1 = "test\n";
  std::string text2 = "hello\n";
  for (size_t i = 0; i < text1.length(); i++)
  {
    m_char_queue.state.get_return_value.push_back(text1[i]);
  }
  for (size_t i = 0; i < text2.length(); i++)
  {
    m_char_queue.state.get_return_value.push_back(text2[i]);
  }

  // When
  for (size_t i = 0; i < text1.length() + text2.length(); i++)
  {
    m_command_line_interface.RunThreadTask();
  }

  // Then
  ASSERT_EQ(2, m_commands.state.run_command_call_count);
  ASSERT_EQ(memcmp(text2.data(), m_commands.state.run_command_keyword.data(), text2.size()), 0);
}

TEST_F(CommandLineInterfaceTests, working_buffer_overflow_resets_the_buffer)
{
  // Given: Buffer fills up
  for (size_t i = 0; i < application::KeywordSize; i++)
  {
    m_char_queue.state.get_return_value.push_back('h');
  }

  // Given: Command sent
  std::string text = "test\n";
  for (size_t i = 0; i < text.length(); i++)
  {
    m_char_queue.state.get_return_value.push_back(text[i]);
  }

  // When
  for (size_t i = 0; i < application::KeywordSize + text.length(); i++)
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
