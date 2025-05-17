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
    m_commands(m_command_array, 2)
  {
  }

protected:
  MockCommand m_command_1;
  MockCommand m_command_2;
  const std::array<ICommand*, MaxCommandsSize> m_command_array = {&m_command_1, &m_command_2};
  Commands m_commands;
};

TEST_F(CommandsTests, sample)
{
  ASSERT_FALSE(true);
}
