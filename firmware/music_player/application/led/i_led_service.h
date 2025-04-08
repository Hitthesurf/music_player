#pragma once

namespace application
{

class ILedService
{
public:
  virtual ~ILedService() = default;

  virtual void Init() const = 0;

  virtual void RunTask() const = 0;
};

}
