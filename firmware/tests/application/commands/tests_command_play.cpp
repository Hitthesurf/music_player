#include "command_line_interface/commands/play.h"
#include "mock_song_player.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::application::commands;
using namespace ::threads;
using namespace ::tests;

class PlayTests : public testing::Test
{
public:
  PlayTests() :
    m_play(m_song_player, m_char_queue)
  {
  }

protected:
  MockSongPlayer m_song_player{};
  MockCharQueue m_char_queue{};
  Play m_play;
};

TEST_F(PlayTests, get_keyword_returns_correct_keyword)
{
  // When
  std::array<char, application::KeywordSize> keyword = m_play.GetKeyword();

  // Then
  std::string keyword_str(keyword.begin(), std::find(keyword.begin(), keyword.end(), '\0'));
  ASSERT_EQ("play\n", keyword_str);
}

TEST_F(PlayTests, executing_play_comamnd_calls_play_on_song_player)
{
  // When
  m_play.Execute();

  // Then
  ASSERT_EQ(1, m_song_player.state.play_call_count);
}

TEST_F(PlayTests, executing_play_comamnd_outputs_command)
{
  // Given
  std::string text = "play\n";

  // When
  m_play.Execute();

  // Then
  ASSERT_EQ(text.length(), m_char_queue.state.add_call_count);
  ASSERT_TRUE(std::equal(text.begin(), text.end(), m_char_queue.state.add_letter.begin()));
}
