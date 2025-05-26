#include "command_line_interface/commands/pause.h"
#include "mock_song_player.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::application::commands;
using namespace ::threads;
using namespace ::tests;

class PauseTests : public testing::Test
{
public:
  PauseTests() :
    m_pause(m_song_player, m_char_queue)
  {
  }

protected:
  MockSongPlayer m_song_player{};
  MockCharQueue m_char_queue{};
  Pause m_pause;
};

TEST_F(PauseTests, get_keyword_returns_correct_keyword)
{
  // Given
  const std::string text = "pause\n";

  // When
  const std::array<char, application::KeywordSize> keyword = m_pause.GetKeyword();

  // Then
  ASSERT_TRUE(std::equal(text.begin(), text.end(), keyword.begin()));
}

TEST_F(PauseTests, executing_pause_comamnd_calls_pause_on_song_player)
{
  // When
  m_pause.Execute();

  // Then
  ASSERT_EQ(1, m_song_player.state.pause_call_count);
}

TEST_F(PauseTests, executing_pause_comamnd_outputs_command)
{
  // Given
  const std::string text = "pause\n";

  // When
  m_pause.Execute();

  // Then
  ASSERT_EQ(text.length(), m_char_queue.state.add_call_count);
  ASSERT_TRUE(std::equal(text.begin(), text.end(), m_char_queue.state.add_letter.begin()));
}
