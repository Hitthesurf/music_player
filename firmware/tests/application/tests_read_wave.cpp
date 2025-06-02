#include "read_music/read_wave.h"
#include "threads/file/mock_secure_digital_storage.h"
#include <cstring>
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::threads;
using namespace ::tests;

class ReadWaveTests : public testing::Test
{
public:
  ReadWaveTests() :
    m_read_wave(m_sd_storage)
  {
  }

protected:
  MockSecureDigitalStorage m_sd_storage;
  ReadWave m_read_wave;
  const size_t wave_info_size = 44;
  const std::array<uint8_t, max_data_read_size> wave_data = {0x00, 0x00, 0x00, 0x00, 0x24, 0x17, 0x1e, 0xf3, 0x3c, 0x13,
    0x3c, 0x14, 0x16, 0xf9, 0x18, 0xf9, 0x34, 0xe7, 0x23, 0xa6, 0x3c, 0xf2, 0x24, 0xf2, 0x11, 0xce, 0x1a, 0x0d};
  const size_t wave_data_size = 28;
};

TEST_F(ReadWaveTests, read_wave_calls_open_file)
{
  // Given
  FileName file_name = {};
  std::memcpy(file_name.data(), "Test.wav", strlen("Test.wav") + 1);

  // When
  m_read_wave.ReadInfo(file_name);

  // Then
  ASSERT_EQ(1, m_sd_storage.state.open_file_call_count);
  ASSERT_EQ(0, std::strncmp(file_name.data(), m_sd_storage.state.open_file_name.front().data(), file_name.size()));
}

TEST_F(ReadWaveTests, read_wave_calculates_the_correct_sample_rate_and_sets_file_pointer_to_end_of_info_section)
{
  // Given
  const FileName file_name = {'T', 'e', 's', 't', '.', 'w', 'a', 'v'};
  const std::array<uint8_t, max_data_read_size> wave_info = {
    0x52, 0x49, 0x46, 0x46, // RIFF
    0x24, 0x08, 0x00, 0x00, // Chunk Size
    0x57, 0x41, 0x56, 0x45, // WAVE
    0x66, 0x6d, 0x74, 0x20, // fmt
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size
    0x01, 0x00,             // Audio Format (PCM)
    0x02, 0x00,             // Number Channels
    0x22, 0x56, 0x00, 0x00, // SampleRate 22050
    0x88, 0x58, 0x01, 0x00, // ByteRate 88200
    0x04, 0x00,             // Block Align 4
    0x10, 0x00,             // Bits Per Sample 16
    0x64, 0x61, 0x74, 0x61, // data
    0x00, 0x08, 0x00, 0x00, // Subchunk2Size
  };
  m_sd_storage.state.read_file_data.push(wave_info);
  m_sd_storage.state.read_file_bytes_received.push(wave_info_size);

  // When
  const ReadInfoResult result = m_read_wave.ReadInfo(file_name);
  const uint32_t sample_rate = m_read_wave.GetSampleRate();

  // Then
  ASSERT_EQ(1, m_sd_storage.state.read_file_call_count);
  ASSERT_EQ(wave_info_size, m_sd_storage.state.read_file_bytes_to_read.back());
  ASSERT_EQ(ReadInfoResult::ReadSuccess, result);
  ASSERT_EQ(22050, sample_rate);
  ASSERT_EQ(1, m_sd_storage.state.seek_point_call_count);
  ASSERT_EQ(wave_info_size, m_sd_storage.state.last_seek_position);
}

TEST_F(ReadWaveTests, process_data_can_process_the_wave_data_with_2_channels_and_2_bytes_per_sample)
{
  // Given
  const FileName file_name = {'T', 'e', 's', 't', '.', 'w', 'a', 'v'};

  const std::array<uint8_t, max_data_read_size> wave_info = {
    0x52, 0x49, 0x46, 0x46, // RIFF
    0x24, 0x08, 0x00, 0x00, // Chunk Size
    0x57, 0x41, 0x56, 0x45, // WAVE
    0x66, 0x6d, 0x74, 0x20, // fmt
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size
    0x01, 0x00,             // Audio Format (PCM)
    0x02, 0x00,             // Number Channels
    0x22, 0x56, 0x00, 0x00, // SampleRate 22050
    0x88, 0x58, 0x01, 0x00, // ByteRate 88200
    0x04, 0x00,             // Block Align 4
    0x10, 0x00,             // Bits Per Sample 16
    0x64, 0x61, 0x74, 0x61, // data
    0x00, 0x08, 0x00, 0x00, // Subchunk2Size
  };
  m_sd_storage.state.read_file_data.push(wave_info);
  m_sd_storage.state.read_file_bytes_received.push(wave_info_size);

  m_sd_storage.state.read_file_data.push(wave_data);
  m_sd_storage.state.read_file_bytes_received.push(wave_data_size);

  // When
  const ReadInfoResult result = m_read_wave.ReadInfo(file_name);
  StereoSamples samples;
  m_read_wave.ProcessData(samples);

  // Then (Added 128 because in wave 16 bit mode values are stored as signed ints)
  StereoSamples expected_samples = {
    // .left = {0x00, 0x17, 0x13, 0xf9, 0xe7, 0xf2, 0xce},
    // .right = {0x00, 0xf3, 0x14, 0xf9, 0xa6, 0xf2, 0x0d},
    .left = {0x80, 0x97, 0x93, 0x79, 0x67, 0x72, 0x4e},
    .right = {0x80, 0x73, 0x94, 0x79, 0x26, 0x72, 0x8d},
    .sample_count = 7
  };
  ASSERT_EQ(4 * max_samples_count, m_sd_storage.state.read_file_bytes_to_read.back());
  ASSERT_EQ(expected_samples.sample_count, samples.sample_count);
  ASSERT_EQ(0, memcmp(expected_samples.left.data(), samples.left.data(), samples.sample_count));
  ASSERT_EQ(0, memcmp(expected_samples.right.data(), samples.right.data(), samples.sample_count));
  ASSERT_EQ(2, m_sd_storage.state.seek_point_call_count); // Note initial call from ReadInfo
  const size_t expected_seek_point = wave_info_size + wave_data_size;
  ASSERT_EQ(expected_seek_point, m_sd_storage.state.last_seek_position);
}

TEST_F(ReadWaveTests, process_data_can_process_the_wave_data_with_1_channel_and_2_bytes_per_sample)
{
  // Given
  const FileName file_name = {'T', 'e', 's', 't', '.', 'w', 'a', 'v'};

  const std::array<uint8_t, max_data_read_size> wave_info = {
    0x52, 0x49, 0x46, 0x46, // RIFF
    0x24, 0x08, 0x00, 0x00, // Chunk Size
    0x57, 0x41, 0x56, 0x45, // WAVE
    0x66, 0x6d, 0x74, 0x20, // fmt
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size
    0x01, 0x00,             // Audio Format (PCM)
    0x01, 0x00,             // Number Channels
    0x22, 0x56, 0x00, 0x00, // SampleRate 22050
    0x44, 0xAC, 0x00, 0x00, // ByteRate 44100
    0x02, 0x00,             // Block Align 2
    0x10, 0x00,             // Bits Per Sample 16
    0x64, 0x61, 0x74, 0x61, // data
    0x00, 0x08, 0x00, 0x00, // Subchunk2Size
  };
  m_sd_storage.state.read_file_data.push(wave_info);
  m_sd_storage.state.read_file_bytes_received.push(wave_info_size);

  m_sd_storage.state.read_file_data.push(wave_data);
  m_sd_storage.state.read_file_bytes_received.push(wave_data_size);

  // When
  const ReadInfoResult result = m_read_wave.ReadInfo(file_name);
  StereoSamples samples;
  m_read_wave.ProcessData(samples);

  // Then (Added 128 because in wave 16 bit mode values are stored as signed ints)
  StereoSamples expected_samples = {
    // .left = {0x00, 0x00, 0x17, 0xf3, 0x13, 0x14, 0xf9, 0xf9, 0xe7, 0xa6, 0xf2, 0xf2, 0xce, 0x0d},
    // .right = {0x00, 0x00, 0x17, 0xf3, 0x13, 0x14, 0xf9, 0xf9, 0xe7, 0xa6, 0xf2, 0xf2, 0xce, 0x0d},
    .left = {0x80, 0x80, 0x97, 0x73, 0x93, 0x94, 0x79, 0x79, 0x67, 0x26, 0x72, 0x72, 0x4e, 0x8d},
    .right = {0x80, 0x80, 0x97, 0x73, 0x93, 0x94, 0x79, 0x79, 0x67, 0x26, 0x72, 0x72, 0x4e, 0x8d},
    .sample_count = 14
  };
  ASSERT_EQ(2 * max_samples_count, m_sd_storage.state.read_file_bytes_to_read.back());
  ASSERT_EQ(expected_samples.sample_count, samples.sample_count);
  ASSERT_EQ(0, memcmp(expected_samples.left.data(), samples.left.data(), samples.sample_count));
  ASSERT_EQ(0, memcmp(expected_samples.right.data(), samples.right.data(), samples.sample_count));
  ASSERT_EQ(2, m_sd_storage.state.seek_point_call_count); // Note initial call from ReadInfo
  const size_t expected_seek_point = wave_info_size + wave_data_size;
  ASSERT_EQ(expected_seek_point, m_sd_storage.state.last_seek_position);
}

TEST_F(ReadWaveTests, process_data_can_process_the_wave_data_with_2_channels_and_1_byte_per_sample)
{
  // Given
  const FileName file_name = {'T', 'e', 's', 't', '.', 'w', 'a', 'v'};

  const std::array<uint8_t, max_data_read_size> wave_info = {
    0x52, 0x49, 0x46, 0x46, // RIFF
    0x24, 0x08, 0x00, 0x00, // Chunk Size
    0x57, 0x41, 0x56, 0x45, // WAVE
    0x66, 0x6d, 0x74, 0x20, // fmt
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size
    0x01, 0x00,             // Audio Format (PCM)
    0x02, 0x00,             // Number Channels
    0x22, 0x56, 0x00, 0x00, // SampleRate 22050
    0x44, 0xAC, 0x00, 0x00, // ByteRate 44100
    0x02, 0x00,             // Block Align 2
    0x08, 0x00,             // Bits Per Sample 8
    0x64, 0x61, 0x74, 0x61, // data
    0x00, 0x08, 0x00, 0x00, // Subchunk2Size
  };
  m_sd_storage.state.read_file_data.push(wave_info);
  m_sd_storage.state.read_file_bytes_received.push(wave_info_size);

  m_sd_storage.state.read_file_data.push(wave_data);
  m_sd_storage.state.read_file_bytes_received.push(wave_data_size);

  // When
  const ReadInfoResult result = m_read_wave.ReadInfo(file_name);
  StereoSamples samples;
  m_read_wave.ProcessData(samples);

  // Then
  StereoSamples expected_samples = {
    .left = {0x00, 0x00, 0x24, 0x1e, 0x3c, 0x3c, 0x16, 0x18, 0x34, 0x23, 0x3c, 0x24, 0x11, 0x1a},
    .right = {0x00, 0x00, 0x17, 0xf3, 0x13, 0x14, 0xf9, 0xf9, 0xe7, 0xa6, 0xf2, 0xf2, 0xce, 0x0d},
    .sample_count = 14
  };
  ASSERT_EQ(2 * max_samples_count, m_sd_storage.state.read_file_bytes_to_read.back());
  ASSERT_EQ(expected_samples.sample_count, samples.sample_count);
  ASSERT_EQ(0, memcmp(expected_samples.left.data(), samples.left.data(), samples.sample_count));
  ASSERT_EQ(0, memcmp(expected_samples.right.data(), samples.right.data(), samples.sample_count));
  ASSERT_EQ(2, m_sd_storage.state.seek_point_call_count); // Note initial call from ReadInfo
  const size_t expected_seek_point = wave_info_size + wave_data_size;
  ASSERT_EQ(expected_seek_point, m_sd_storage.state.last_seek_position);
}

TEST_F(ReadWaveTests, process_data_can_process_the_wave_data_with_1_channel_and_1_byte_per_sample)
{
  // Given
  const FileName file_name = {'T', 'e', 's', 't', '.', 'w', 'a', 'v'};

  const std::array<uint8_t, max_data_read_size> wave_info = {
    0x52, 0x49, 0x46, 0x46, // RIFF
    0x24, 0x08, 0x00, 0x00, // Chunk Size
    0x57, 0x41, 0x56, 0x45, // WAVE
    0x66, 0x6d, 0x74, 0x20, // fmt
    0x10, 0x00, 0x00, 0x00, // Subchunk1Size
    0x01, 0x00,             // Audio Format (PCM)
    0x01, 0x00,             // Number Channels
    0x22, 0x56, 0x00, 0x00, // SampleRate 22050
    0x22, 0x56, 0x00, 0x00, // ByteRate 22050
    0x01, 0x00,             // Block Align 1
    0x08, 0x00,             // Bits Per Sample 8
    0x64, 0x61, 0x74, 0x61, // data
    0x00, 0x08, 0x00, 0x00, // Subchunk2Size
  };
  m_sd_storage.state.read_file_data.push(wave_info);
  m_sd_storage.state.read_file_bytes_received.push(wave_info_size);

  m_sd_storage.state.read_file_data.push(wave_data);
  m_sd_storage.state.read_file_bytes_received.push(wave_data_size);

  // When
  const ReadInfoResult result = m_read_wave.ReadInfo(file_name);
  StereoSamples samples;
  m_read_wave.ProcessData(samples);

  // Then
  // clang-format off
  StereoSamples expected_samples = {
    .left = {0x00, 0x00, 0x00, 0x00, 0x24, 0x17, 0x1e, 0xf3, 0x3c, 0x13, 0x3c, 0x14, 0x16, 0xf9, 0x18, 0xf9, 0x34, 0xe7,
             0x23, 0xa6, 0x3c, 0xf2, 0x24, 0xf2, 0x11, 0xce, 0x1a, 0x0d},
    .right = {0x00, 0x00, 0x00, 0x00, 0x24, 0x17, 0x1e, 0xf3, 0x3c, 0x13, 0x3c, 0x14, 0x16, 0xf9, 0x18, 0xf9, 0x34,
             0xe7, 0x23, 0xa6, 0x3c, 0xf2, 0x24, 0xf2, 0x11, 0xce, 0x1a, 0x0d},
    .sample_count = 28
  };
  // clang-format on
  ASSERT_EQ(max_samples_count, m_sd_storage.state.read_file_bytes_to_read.back());
  ASSERT_EQ(expected_samples.sample_count, samples.sample_count);
  ASSERT_EQ(0, memcmp(expected_samples.left.data(), samples.left.data(), samples.sample_count));
  ASSERT_EQ(0, memcmp(expected_samples.right.data(), samples.right.data(), samples.sample_count));
  ASSERT_EQ(2, m_sd_storage.state.seek_point_call_count); // Note initial call from ReadInfo
  const size_t expected_seek_point = wave_info_size + expected_samples.sample_count;
  ASSERT_EQ(expected_seek_point, m_sd_storage.state.last_seek_position);
}
