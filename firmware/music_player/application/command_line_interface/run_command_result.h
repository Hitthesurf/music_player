#pragma once
#include <cstdint>

namespace application
{

enum class RunCommandResult : uint8_t
{
  CommandFound,
  NoCommandFound
};

}
