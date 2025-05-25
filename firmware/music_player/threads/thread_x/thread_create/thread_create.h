#pragma once

#include "thread_create/i_thread_create.h"
#include "tx_api.h"
#include <array>
#include <cstdint>

namespace threads
{

class ThreadCreate : public IThreadCreate
{
public:
  ThreadCreate(uint32_t* stack, size_t stack_size, void (*task)(ULONG));

private:
  TX_THREAD m_thread;
  static constexpr UINT m_priority = 5; // Thread priority (lower value = higher priority)
};

}
