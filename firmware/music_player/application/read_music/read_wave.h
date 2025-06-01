#pragma once
#include "file/i_secure_digital_storage.h"
#include "read_music/i_read_music.h"

namespace application
{
class ReadWave : public IReadMusic
{
public:
  ReadWave(threads::ISecureDigitalStorage& sd_storage);
  ReadInfoResult ReadInfo(threads::FileName name) override;
  void ProcessData(StereoSamples& stereo_samples) override;
  uint32_t GetSampleRate() const override;

private:
  uint32_t UINT32_LE(const uint8_t data[]);
  uint16_t UINT16_LE(const uint8_t data[]);

  const size_t wave_info_size = 44;
  threads::ISecureDigitalStorage& m_sd_storage;
  size_t m_file_seek_point = 0;
  uint16_t m_number_of_channels = 0;
  uint32_t m_sample_rate = 0;
  uint32_t m_byte_rate = 0;
  uint16_t m_block_align = 0;
  uint16_t m_bits_per_sample = 0;
  uint32_t m_size_of_data = 0;
};
}
