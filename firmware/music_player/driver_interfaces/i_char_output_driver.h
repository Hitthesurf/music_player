#pragma once

namespace drivers
{

class ICharOutputDriver
{
public:
  virtual ~ICharOutputDriver() = default;
  virtual void Init() const = 0;
  virtual void Output(char text) const = 0;
};

}
