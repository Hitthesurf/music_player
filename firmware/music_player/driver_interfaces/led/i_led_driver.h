#pragma once

namespace drivers
{

class ILedDriver
{
public:
  virtual ~ILedDriver() = default;
  virtual void Init() const = 0;
  virtual void Toggle() const = 0;
};

}
