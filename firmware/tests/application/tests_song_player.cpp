#include "drivers/mock_pwm_driver.h"
#include "song_player.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::tests;

class SongPlayerTests : public testing::Test
{
public:
  SongPlayerTests() :
    m_song_player(m_song_driver)
  {
  }

protected:
  MockPWMDriver m_song_driver{};
  SongPlayer m_song_player;
};

TEST_F(SongPlayerTests, play_calls_song_driver_play)
{
  // When
  m_song_player.Play();

  // Then
  ASSERT_EQ(1, m_song_driver.state.play_call_count);
}

TEST_F(SongPlayerTests, pause_calls_song_driver_stop)
{
  // When
  m_song_player.Pause();

  // Then
  ASSERT_EQ(1, m_song_driver.state.stop_call_count);
}

TEST_F(SongPlayerTests, next_note_loads_next_note_into_song_driver)
{
  // When
  m_song_player.NextNote();

  // Then
  ASSERT_EQ(1, m_song_driver.state.load_left_call_count);
  ASSERT_EQ(1, m_song_driver.state.load_right_call_count);
}
