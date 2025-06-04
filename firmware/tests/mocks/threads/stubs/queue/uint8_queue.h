#pragma once

#include "queue/defines.h"
#include "queue/i_uint8_queue.h"
#include <array>
#include <cstdint>

namespace threads
{

class Uint8Queue : public IUint8Queue
{
public:
  Uint8Queue(std::array<uint32_t, uint8_queue_size>& queue_data, size_t queue_window_size)
  {
    (void)queue_data;
    (void)queue_window_size;
  }

  void Add(uint8_t id)
  {
    (void)id;
  }

  void AddIsr(uint8_t id)
  {
    (void)id;
  }

  [[nodiscard]]
  uint8_t Get()
  {
    return 0;
  }

  [[nodiscard]]
  uint8_t GetIsr()
  {
    return 0;
  }
};

}
