#pragma once

namespace application
{

class ICommandLineInterface
{
public:
  virtual ~ICommandLineInterface() = default;

  virtual void Init() const = 0;
  virtual void RunThreadTask() = 0;
};

}
