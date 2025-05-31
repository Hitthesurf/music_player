#pragma once
#include "fx_api.h"
#include <array>
#include <cstddef>
#include <cstdint>

namespace threads
{
constexpr size_t max_data_read_size = 100;
using FileName = std::array<char, FX_MAX_LONG_NAME_LEN>;
using FileData = std::array<uint8_t, max_data_read_size>;

enum class NextFileResult : uint8_t
{
  FileFound,
  NoFileFound
};

}
