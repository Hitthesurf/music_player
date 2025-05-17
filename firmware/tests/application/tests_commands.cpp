#include "command_line_interface/commands.h"
#include "command_line_interface/defines.h"
#include "command_line_interface/mock_command.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::tests;

class CommandsTests : public testing::Test
{
public:
  CommandsTests() :
    m_commands(m_command_array, m_command_count)
  {
    m_command_1.state.get_keyword_return_value = m_command_1_keyword;
    m_command_2.state.get_keyword_return_value = m_command_2_keyword;
  }

protected:
  MockCommand m_command_1;
  MockCommand m_command_2;
  static constexpr size_t m_command_count = 2;
  const std::array<ICommand*, MaxCommandsSize> m_command_array = {&m_command_1, &m_command_2};
  Commands m_commands;

  const std::array<char, application::KeywordSize> m_command_1_keyword = {'c', 'o', 'm', 'm', 'a', 'n', 'd', '_', '1',
    '\n'};
  const std::array<char, application::KeywordSize> m_command_2_keyword = {'c', 'o', 'm', 'm', 'a', 'n', 'd', '_', '2',
    '\n'};
};

TEST_F(CommandsTests, does_not_execute_command_it_keyword_does_not_match)
{
  // Given
  std::array<char, application::KeywordSize> text = {'t', 'e', 's', 't', '\n'};

  // When
  RunCommandResult result = m_commands.RunCommand(text);

  // Then
  ASSERT_EQ(m_command_1.state.execute_call_count, 0);
  ASSERT_EQ(m_command_2.state.execute_call_count, 0);
  ASSERT_EQ(result, RunCommandResult::NoCommandFound);

  // But still compared
  ASSERT_EQ(m_command_1.state.get_keyword_call_count, 1);
  ASSERT_EQ(m_command_2.state.get_keyword_call_count, 1);
}
