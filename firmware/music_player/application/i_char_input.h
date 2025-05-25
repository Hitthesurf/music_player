#pragma once

namespace application
{

class ICharInput
{
public:
  virtual ~ICharInput() = default;
  virtual void Input(const char text) = 0;
};

}
