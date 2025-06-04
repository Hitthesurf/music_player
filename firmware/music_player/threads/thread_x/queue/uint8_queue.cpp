#include "queue/uint8_queue.h"

using namespace ::threads;

Uint8Queue::Uint8Queue(std::array<uint32_t, uint8_queue_size>& queue_data, size_t queue_window_size)
{
  CHAR name[] = "tx_uint8_queue";
  constexpr UINT message_size = TX_1_ULONG;
  const size_t queue_size = queue_window_size > queue_data.size() ? queue_data.size() : queue_window_size;
  tx_queue_create(&m_tx_queue, name, message_size, queue_data.data(), queue_size * sizeof(uint32_t));
}

void Uint8Queue::Add(uint8_t id)
{
  ULONG message = static_cast<ULONG>(id);
  tx_queue_send(&m_tx_queue, &message, TX_WAIT_FOREVER);
}

void Uint8Queue::AddIsr(uint8_t id)
{
  ULONG message = static_cast<ULONG>(id);
  tx_queue_send(&m_tx_queue, &message, TX_NO_WAIT);
}

[[nodiscard]]
uint8_t Uint8Queue::Get()
{
  ULONG message = 0;
  tx_queue_receive(&m_tx_queue, &message, TX_WAIT_FOREVER);
  return static_cast<uint8_t>(message);
}

[[nodiscard]]
uint8_t Uint8Queue::GetIsr()
{
  ULONG message = 0;
  ULONG status = tx_queue_receive(&m_tx_queue, &message, TX_NO_WAIT);
  if (status != 0)
  {
    return 10;
  }
  return static_cast<uint8_t>(message);
}
