#pragma once

#include <cstddef>

namespace threads
{

class IThreadUtils
{
public:
  virtual ~IThreadUtils() = default;
  virtual void Sleep(size_t sleep_ms) = 0;
};

}
