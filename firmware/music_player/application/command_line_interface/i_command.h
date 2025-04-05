#pragma once

#include <array>
#include <cstddef>

namespace application
{

constexpr std::size_t KEYWORD_SIZE = 16;

class ICommand
{
public:
  virtual ~ICommand() = default;

  virtual void Execute(const size_t argc, char* argv[]) const = 0;

protected:
  const std::array<char, KEYWORD_SIZE> m_keyword;
};

}
