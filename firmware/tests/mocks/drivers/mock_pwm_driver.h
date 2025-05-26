#pragma once

#include "i_song_driver.h"
#include <cstddef>
#include <cstdint>

namespace tests
{

class MockPWMDriver : public drivers::ISongDriver
{
public:
  void Config(size_t sample_rate)
  {
    state.config_call_count++;
    state.last_sample_rate = sample_rate;
  }

  void LoadLeft(uint8_t value)
  {
    state.load_left_call_count++;
    state.last_left_value = value;
  }

  void LoadRight(uint8_t value)
  {
    state.load_right_call_count++;
    state.last_right_value = value;
  }

  void Play()
  {
    state.play_call_count++;
  }

  void Stop()
  {
    state.stop_call_count++;
  }

  struct StateType
  {
    size_t config_call_count = 0;
    size_t load_left_call_count = 0;
    size_t load_right_call_count = 0;
    size_t play_call_count = 0;
    size_t stop_call_count = 0;

    size_t last_sample_rate = 0;
    uint8_t last_left_value = 0;
    uint8_t last_right_value = 0;
  } mutable state{};
};

}
