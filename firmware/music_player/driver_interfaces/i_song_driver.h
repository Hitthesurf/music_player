#pragma once

#include <cstddef>
#include <cstdint>

namespace drivers
{

class ISongDriver
{
public:
  virtual ~ISongDriver() = default;
  virtual void Config(size_t sample_rate) = 0;
  virtual void LoadLeft(uint8_t value) = 0;
  virtual void LoadRight(uint8_t value) = 0;
  virtual void Play() = 0;
  virtual void Stop() = 0;
  virtual void TimerAuxPwmPeriodElapsedCallback() = 0;
};

}
