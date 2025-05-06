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

  virtual void Execute(const size_t argc, char* argv[]) const = 0;

protected:
  const std::array<char, KeywordSize> m_keyword;
};

}
