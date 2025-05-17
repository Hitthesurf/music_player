#pragma once

#include "queue/defines.h"
#include "queue/i_char_queue.h"
#include "tx_api.h"
#include <array>
#include <cstdint>

namespace threads
{

class CharQueue : ICharQueue
{
public:
  CharQueue(std::array<uint32_t, char_queue_size>& queue_data);

  void Init() const override;
  void Add(char letter) override;

  [[nodiscard]]
  char Get() override;

private:
  TX_QUEUE m_tx_queue;
};

}
