#pragma once
#include <array>
#include <cstddef>
#include <cstdint>

namespace application
{
constexpr size_t max_samples_count = 128;
using SampleData = std::array<uint8_t, max_samples_count>;

enum class ReadInfoResult : uint8_t
{
  ReadError,
  ReadSuccess
};

struct StereoSamples
{
  SampleData left;
  SampleData right;
  size_t sample_count = 0;
};

}
