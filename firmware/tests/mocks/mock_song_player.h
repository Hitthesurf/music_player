#pragma once

#include "i_song_player.h"
#include <cstddef>

namespace tests
{

class MockSongPlayer : public application::ISongPlayer
{
public:
  void NextNote() override
  {
    state.next_note_call_count++;
  }

  void Play() const override
  {
    state.play_call_count++;
  }

  void Pause() const override
  {
    state.pause_call_count++;
  }

  void TimerLoadAudioPeriodElapsedCallback() override
  {
    state.timer_callback_call_count++;
  }

  struct StateType
  {
    size_t next_note_call_count = 0;
    size_t play_call_count = 0;
    size_t pause_call_count = 0;
    size_t timer_callback_call_count = 0;
  } mutable state{};
};

}
