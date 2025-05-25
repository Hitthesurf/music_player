#pragma once

namespace threads
{

class ICharQueue
{
public:
  virtual ~ICharQueue() = default;

  virtual void Init() const = 0;
  virtual void Add(char letter) = 0;
  virtual void AddIsr(char letter) = 0;
  virtual char Get() = 0;
};

}
