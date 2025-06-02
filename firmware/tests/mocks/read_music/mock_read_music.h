#include "read_music/i_read_music.h"
#include <queue>

namespace tests
{

class MockReadMusic : public application::IReadMusic
{
public:
  application::ReadInfoResult ReadInfo(threads::FileName name) override
  {
    state.read_info_call_count++;
    state.last_read_info_filename = name;
    return state.read_info_return_value;
  }

  void ProcessData(application::StereoSamples& stereo_samples) override
  {
    state.process_data_call_count++;
    state.last_stereo_samples.push(stereo_samples);
  }

  uint32_t GetSampleRate() const override
  {
    state.get_sample_rate_call_count++;
    return state.get_sample_rate_return_value;
  }

  struct StateType
  {
    size_t read_info_call_count = 0;
    threads::FileName last_read_info_filename{};
    application::ReadInfoResult read_info_return_value = application::ReadInfoResult::ReadSuccess;

    size_t process_data_call_count = 0;
    std::queue<application::StereoSamples> last_stereo_samples{};

    size_t get_sample_rate_call_count = 0;
    uint32_t get_sample_rate_return_value = 0;
  } mutable state{};
};

}
