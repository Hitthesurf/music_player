#include "thread_utils.h"
#include "tx_api.h"

using namespace ::threads;

void ThreadUtils::Sleep(size_t sleep_ms)
{
  const ULONG ticks = (TX_TIMER_TICKS_PER_SECOND * sleep_ms) / 1000;
  tx_thread_sleep(ticks);
}
