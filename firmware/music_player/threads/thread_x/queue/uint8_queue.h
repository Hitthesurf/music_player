#pragma once

#include "queue/defines.h"
#include "queue/i_uint8_queue.h"
#include "tx_api.h"
#include <array>
#include <cstdint>

namespace threads
{

class Uint8Queue : public IUint8Queue
{
public:
  Uint8Queue(std::array<uint32_t, uint8_queue_size>& queue_data, size_t queue_window_size);

  void Add(uint8_t id) override;
  void AddIsr(uint8_t id) override;

  [[nodiscard]]
  uint8_t Get() override;
  [[nodiscard]]
  uint8_t GetIsr() override;

private:
  TX_QUEUE m_tx_queue;
};

}
