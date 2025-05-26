#pragma once

#include "queue/defines.h"
#include "queue/i_char_queue.h"
#include <array>
#include <cstdint>

namespace threads
{

class CharQueue : public ICharQueue
{
public:
  explicit CharQueue(std::array<uint32_t, char_queue_size>& queue_data) {}

  void Init() const override
  {
    // Stub: no implementation needed for tests.
  }

  void Add(char letter) override
  {
    // Stub: no implementation needed for tests.
  }

  void AddIsr(char letter) override
  {
    // Stub: no implementation needed for tests.
  }

  [[nodiscard]]
  char Get() override
  {
    return 'h';
  }
};

}
