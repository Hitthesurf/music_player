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
  FileName file_name = {};
  std::memcpy(file_name.data(), "Test.wav", strlen("Test.wav") + 1);
  // clang-format off
  std::array<uint8_t, max_data_read_size> info_data =
   {
    0x52, 0x49, 0x46, 0x46, 0x24, 0x08, 0x00, 0x00, 0x57, 0x41, 0x56,
    0x45, 0x66, 0x6d, 0x74, 0x20, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00,
     0x02, 0x00, 0x22, 0x56, 0x00, 0x00, 0x88, 0x58,
    0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x08, 0x00, 0x00};
  m_sd_storage.state.read_file_data.push(info_data);
  // clang-format on
  m_sd_storage.state.read_file_data_size.push(44);

  // When
  const ReadInfoResult result = m_read_wave.ReadInfo(file_name);
  const uint32_t sample_rate = m_read_wave.GetSampleRate();

  // Then
  ASSERT_EQ(1, m_sd_storage.state.read_file_call_count);
  ASSERT_EQ(ReadInfoResult::ReadSuccess, result);
  ASSERT_EQ(22050, sample_rate);
  ASSERT_EQ(1, m_sd_storage.state.seek_point_call_count);
  ASSERT_EQ(44, m_sd_storage.state.last_seek_position);
}

TEST_F(ReadWaveTests, process_data_can_process_the_wave_data)
{
  // Given
  FileName file_name = {};
  std::memcpy(file_name.data(), "Test.wav", strlen("Test.wav") + 1);
  // clang-format off
  std::array<uint8_t, max_data_read_size> info_data =
   {
    0x52, 0x49, 0x46, 0x46, 0x24, 0x08, 0x00, 0x00, 0x57, 0x41, 0x56,
    0x45, 0x66, 0x6d, 0x74, 0x20, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00,
     0x02, 0x00, 0x22, 0x56, 0x00, 0x00, 0x88, 0x58,
    0x01, 0x00, 0x04, 0x00, 0x10, 0x00, 0x64, 0x61, 0x74, 0x61, 0x00, 0x08, 0x00, 0x00,};
  m_sd_storage.state.read_file_data.push(info_data);
  m_sd_storage.state.read_file_data_size.push(44);
  // clang-format on
  std::array<uint8_t, max_data_read_size> data = {0x00, 0x00, 0x00, 0x00, 0x24, 0x17, 0x1e, 0xf3, 0x3c, 0x13, 0x3c,
    0x14, 0x16, 0xf9, 0x18, 0xf9, 0x34, 0xe7, 0x23, 0xa6, 0x3c, 0xf2, 0x24, 0xf2, 0x11, 0xce, 0x1a, 0x0d};
  m_sd_storage.state.read_file_data.push(data);
  m_sd_storage.state.read_file_data_size.push(28);

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
  ASSERT_EQ(expected_samples.sample_count, samples.sample_count);
  ASSERT_EQ(0, memcmp(expected_samples.left.data(), samples.left.data(), samples.sample_count));
  ASSERT_EQ(0, memcmp(expected_samples.right.data(), samples.right.data(), samples.sample_count));
}
