#pragma once

#include "command_line_interface/defines.h"
#include <array>
#include <cstddef>

namespace application
{

class ICommand
{
public:
  virtual ~ICommand() = default;

  virtual void Execute() const = 0;

  [[nodiscard]]
  virtual std::array<char, KeywordSize> GetKeyword() const = 0;
};

}
