#pragma once
#include <array>
#include <cstddef>

namespace drivers
{
constexpr size_t max_data_read_size = 100;
constexpr size_t max_file_name_size = 100;
using FileName = std::array<uint8_t, max_file_name_size>;
using FileData = std::array<uint8_t, max_file_name_size>;

enum class NextFileResult : uint8_t
{
  FileFound,
  NoFileFound
};

}
