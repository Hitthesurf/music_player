#pragma once

namespace threads
{

class ICharQueue
{
public:
  virtual ~ICharQueue() = default;

  virtual void Init() const = 0;
  virtual void Add(char letter) const = 0;
  virtual char Get() const = 0;
};

}
