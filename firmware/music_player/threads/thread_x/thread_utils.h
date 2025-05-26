#pragma once

#include "i_thread_utils.h"

namespace threads
{

class ThreadUtils : public IThreadUtils
{
public:
  ThreadUtils() = default;
  void Sleep(size_t sleep_ms) override;
};

}
