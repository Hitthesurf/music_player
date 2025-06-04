#pragma once

#include <cstdint>

namespace threads
{

class IUint8Queue
{
public:
  virtual ~IUint8Queue() = default;

  virtual void Add(uint8_t id) = 0;
  virtual void AddIsr(uint8_t id) = 0;
  virtual uint8_t Get() = 0;
  virtual uint8_t GetIsr() = 0;
};

}
