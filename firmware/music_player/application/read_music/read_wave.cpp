#include "read_music/read_wave.h"
#include <cstring>

namespace application
{

uint32_t ReadWave::UINT32_LE(const uint8_t data[])
{
  uint32_t total = data[0];
  total += data[1] << 8;
  total += data[2] << 16;
  total += data[3] << 24;
  return total;
}

uint16_t ReadWave::UINT16_LE(const uint8_t data[])
{
  uint16_t total = data[0];
  total += data[1] << 8;
  return total;
}

ReadWave::ReadWave(threads::ISecureDigitalStorage& sd_storage) :
  m_sd_storage(sd_storage)
{
}

ReadInfoResult ReadWave::ReadInfo(threads::FileName name)
{
  m_sd_storage.OpenFile(name);
  threads::FileData wave_file;
  size_t wave_file_size = 0;
  m_sd_storage.ReadFile(wave_file, wave_info_size, wave_file_size);

  if (wave_file_size < wave_info_size)
    return ReadInfoResult::ReadError;

  size_t pointer = 0;
  int status = 0;
  // Check RIFF
  constexpr size_t riff_size = 4;
  status = memcmp(&wave_file[pointer], "RIFF", riff_size);
  if (status != 0)
    return ReadInfoResult::ReadError;
  pointer += riff_size;

  // Skip Chunk Size
  pointer += 4;

  // Check WAVE
  constexpr size_t wave_size = 4;
  status = memcmp(&wave_file[pointer], "WAVE", wave_size);
  if (status != 0)
    return ReadInfoResult::ReadError;
  pointer += wave_size;

  // Check fmt
  constexpr size_t fmt_size = 4;
  constexpr uint8_t fmt_value[] = {0x66, 0x6d, 0x74, 0x20};
  status = memcmp(&wave_file[pointer], fmt_value, fmt_size);
  if (status != 0)
    return ReadInfoResult::ReadError;
  pointer += fmt_size;

  // Check sub chunck 1 size is 16
  const uint32_t sub_chunck_1_size = UINT32_LE(&wave_file[pointer]);
  if (sub_chunck_1_size != 16)
    return ReadInfoResult::ReadError;
  pointer += 4;

  // Check audio format is 1
  constexpr uint16_t PCM = 1;
  const uint16_t audio_format = UINT16_LE(&wave_file[pointer]);
  if (audio_format != PCM)
    return ReadInfoResult::ReadError;
  pointer += 2;

  // Get Number of channels
  const uint16_t number_of_channels = UINT16_LE(&wave_file[pointer]);
  if ((number_of_channels != 1) && (number_of_channels != 2))
    return ReadInfoResult::ReadError;
  pointer += 2;

  // Get Sample Rate
  const uint32_t sample_rate = UINT32_LE(&wave_file[pointer]);
  pointer += 4;

  // Get Byte Rate
  const uint32_t byte_rate = UINT32_LE(&wave_file[pointer]);
  pointer += 4;

  // Get Block Align
  const uint16_t block_align = UINT16_LE(&wave_file[pointer]);
  pointer += 2;

  // Get BitsPerSample
  const uint16_t bits_per_sample = UINT16_LE(&wave_file[pointer]);
  pointer += 2;

  // Check data
  constexpr size_t data_chunck_id_size = 4;
  status = memcmp(&wave_file[pointer], "data", data_chunck_id_size);
  if (status != 0)
    return ReadInfoResult::ReadError;
  pointer += data_chunck_id_size;

  // Get Data chunk size
  const uint32_t size_of_data = UINT32_LE(&wave_file[pointer]);
  pointer += 4;

  // Save wanted data to struct
  m_number_of_channels = number_of_channels;
  m_sample_rate = sample_rate;
  m_byte_rate = byte_rate;
  m_block_align = block_align;
  m_bits_per_sample = bits_per_sample;
  m_size_of_data = size_of_data;

  m_file_seek_point = wave_info_size;
  m_sd_storage.SeekPointInFile(m_file_seek_point);

  return ReadInfoResult::ReadSuccess;
}

void ReadWave::ProcessData(StereoSamples& stereo_samples)
{
  const size_t bytes_per_sample = m_bits_per_sample >> 3; // Divide by 8
  const size_t jump_number = m_block_align;
  const size_t left_channel_id = 0;
  const size_t right_channel_id = m_number_of_channels - 1;
  const size_t left_offset = left_channel_id * bytes_per_sample + bytes_per_sample - 1;
  const size_t right_offset = right_channel_id * bytes_per_sample + bytes_per_sample - 1;
  const uint8_t signed_offset = 128 * (bytes_per_sample - 1); // Because wave file stores them as int

  threads::FileData data;
  size_t data_size = 0;
  const size_t bytes_to_read = max_samples_count * m_block_align;
  m_sd_storage.ReadFile(data, bytes_to_read, data_size);

  const size_t available_blocks_to_process = data_size / m_block_align;
  const size_t blocks_to_process =
    available_blocks_to_process > max_samples_count ? max_samples_count : available_blocks_to_process;
  for (size_t i = 0; i < blocks_to_process; i++)
  {
    stereo_samples.left.at(i) = data.at(left_offset + jump_number * i) + signed_offset;
    stereo_samples.right.at(i) = data.at(right_offset + jump_number * i) + signed_offset;
  }
  stereo_samples.sample_count = blocks_to_process;
  m_file_seek_point += blocks_to_process * m_block_align;
  m_sd_storage.SeekPointInFile(m_file_seek_point);
}

uint32_t ReadWave::GetSampleRate() const
{
  return m_sample_rate;
}
}
