#pragma once
#include "file/i_secure_digital_storage.h"
#include "read_music/i_read_music.h"

namespace application
{
class ReadWave : public IReadMusic
{
public:
  ReadWave(threads::ISecureDigitalStorage& sd_storage);
  void ReadInfo(threads::FileName name) override;
  void ProcessData(StereoSamples& stereo_samples) override;
  uint32_t GetSampleRate() const override;

private:
  threads::ISecureDigitalStorage& m_sd_storage;
};
}
