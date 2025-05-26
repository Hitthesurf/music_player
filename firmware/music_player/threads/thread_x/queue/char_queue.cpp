#include "queue/char_queue.h"

using namespace ::threads;

CharQueue::CharQueue(std::array<uint32_t, char_queue_size>& queue_data)
{
  CHAR name[] = "tx_message_queue";
  constexpr UINT message_size = TX_1_ULONG;

  tx_queue_create(&m_tx_queue, name, message_size, queue_data.data(), queue_data.size() * sizeof(uint32_t));
}

void CharQueue::Add(char letter)
{
  ULONG message = static_cast<ULONG>(letter);
  tx_queue_send(&m_tx_queue, &message, TX_WAIT_FOREVER);
}

void CharQueue::AddIsr(char letter)
{
  ULONG message = static_cast<ULONG>(letter);
  tx_queue_send(&m_tx_queue, &message, TX_NO_WAIT);
}

[[nodiscard]]
char CharQueue::Get()
{
  ULONG message = 0;
  tx_queue_receive(&m_tx_queue, &message, TX_WAIT_FOREVER);
  return static_cast<char>(message);
}
