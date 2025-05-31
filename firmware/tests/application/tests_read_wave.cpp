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
