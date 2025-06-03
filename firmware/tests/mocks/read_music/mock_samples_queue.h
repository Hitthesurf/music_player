#include "read_music/i_samples_queue.h"
#include <queue>

namespace tests
{
class MockSamplesQueue : public application::ISamplesQueue
{
public:
  application::StereoSamples& AddSampleLocation() override
  {
    state.add_sample_location_call_count++;
    return state.add_sample_location_return_value;
  }

  void AddSampleStored() override
  {
    state.add_sample_stored_call_count++;
  }

  application::StereoSamples& GetISR() override
  {
    state.get_isr_call_count++;
    return state.get_isr_return_value;
  }

  struct StateType
  {
    size_t add_sample_location_call_count = 0;
    size_t add_sample_stored_call_count = 0;
    size_t get_isr_call_count = 0;

    application::StereoSamples add_sample_location_return_value;
    application::StereoSamples get_isr_return_value;

  } mutable state{};
};

}
