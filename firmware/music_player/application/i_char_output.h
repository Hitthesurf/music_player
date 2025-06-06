#pragma once

namespace application
{

class ICharOutput
{
public:
  virtual ~ICharOutput() = default;
  virtual void RunThreadTask() const = 0;
  virtual void Output(const char* text) const = 0;
};

}
