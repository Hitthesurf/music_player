#include "thread_create/thread_create.h"

using namespace ::threads;

ThreadCreate::ThreadCreate(uint32_t* stack, size_t stack_size, void (*task)(ULONG))
{
  CHAR name[] = "thread";
  tx_thread_create(&m_thread, name, task, 0, stack, stack_size, m_priority, m_priority, TX_NO_TIME_SLICE,
    TX_AUTO_START);
}
