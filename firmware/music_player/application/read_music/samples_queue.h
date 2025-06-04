#pragma once

#include "queue/uint8_queue.h"
#include "read_music/i_samples_queue.h"

namespace application
{

class SamplesQueue : public ISamplesQueue
{
public:
  SamplesQueue();
  StereoSamples& AddSampleLocation() override;
  void AddSampleStored() override;
  StereoSamples& GetISR() override;

private:
  std::array<StereoSamples, samples_queue_count + 2>
    m_samples_queue_data; // +2 because we want position for reading and writing
  std::array<uint32_t, threads::uint8_queue_size> m_id_queue_data;
  threads::Uint8Queue m_id_queue;
  uint8_t m_current_write_id = 0;
};
}
