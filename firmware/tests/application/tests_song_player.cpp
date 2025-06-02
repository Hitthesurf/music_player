#include "drivers/mock_pwm_driver.h"
#include "file/defines.h"
#include "read_music/mock_read_music.h"
#include "song_player.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::threads;
using namespace ::tests;

class SongPlayerTests : public testing::Test
{
public:
  SongPlayerTests() :
    m_song_player(m_song_driver, m_read_music)
  {
  }

protected:
  MockPWMDriver m_song_driver{};
  MockReadMusic m_read_music{};
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

TEST_F(SongPlayerTests, callback_loads_next_note_into_song_driver)
{
  // When
  m_song_player.TimerLoadAudioPeriodElapsedCallback();

  // Then
  ASSERT_EQ(1, m_song_driver.state.load_left_call_count);
  ASSERT_EQ(1, m_song_driver.state.load_right_call_count);
}

TEST_F(SongPlayerTests, run_task_only_calls_changing_song_functions_once_after_selecting_song)
{
  // Given
  FileName name = {'T', 'e', 's', 't', '.', 'w', 'a', 'e'};
  m_song_player.SelectSong(name);
  const size_t some_sample_rate = 22050;
  m_read_music.state.get_sample_rate_return_value = some_sample_rate;

  // When
  m_song_player.RunStreamThreadTask();
  m_song_player.RunStreamThreadTask();

  // Then
  ASSERT_EQ(1, m_read_music.state.read_info_call_count);
  ASSERT_EQ(0, memcmp(m_read_music.state.last_read_info_filename.data(), name.data(), strlen(name.data())));
  ASSERT_EQ(1, m_read_music.state.get_sample_rate_call_count);
  ASSERT_EQ(1, m_song_driver.state.config_call_count);
  ASSERT_EQ(some_sample_rate, m_song_driver.state.last_sample_rate);
}
