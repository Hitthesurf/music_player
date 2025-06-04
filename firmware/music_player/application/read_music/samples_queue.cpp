#include "read_music/samples_queue.h"

using namespace ::application;

SamplesQueue::SamplesQueue() :
  m_id_queue(m_id_queue_data, samples_queue_count)
{
}

StereoSamples& SamplesQueue::AddSampleLocation()
{
  return m_samples_queue_data.at(m_current_write_id);
}

void SamplesQueue::AddSampleStored()
{
  m_id_queue.Add(m_current_write_id);
  m_current_write_id = (m_current_write_id + 1) % (m_samples_queue_data.size());
}

StereoSamples& SamplesQueue::GetISR()
{
  const uint8_t read_id = m_id_queue.GetIsr();
  if (read_id == 10)
  {
    return m_empty_sample;
  }
  return m_samples_queue_data.at(read_id);
}
