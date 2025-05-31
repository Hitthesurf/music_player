#include "read_music/read_wave.h"

namespace application
{

ReadWave::ReadWave(threads::ISecureDigitalStorage& sd_storage) :
  m_sd_storage(sd_storage)
{
}

void ReadWave::ReadInfo(threads::FileName name)
{
  m_sd_storage.OpenFile(name);
}

void ReadWave::ProcessData(StereoSamples& stereo_samples) {}

uint32_t ReadWave::GetSampleRate() const
{
  return 0;
}
}
