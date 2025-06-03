#pragma once

#include "read_music/i_samples_queue.h"

namespace application
{

class SamplesQueue : public ISamplesQueue
{
public:
  StereoSamples& AddSampleLocation() override;
  void AddSampleStored() override;
  StereoSamples& GetISR() override;

private:
  std::array<StereoSamples, samples_queue_count + 2>
    m_samples_queue_data; // +2 because we want position for reading and writing
};
}
