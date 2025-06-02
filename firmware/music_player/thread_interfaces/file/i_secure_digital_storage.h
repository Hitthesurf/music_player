#pragma once

#include "file/defines.h"
#include <array>
#include <cstdint>

namespace threads
{

class ISecureDigitalStorage
{
public:
  virtual ~ISecureDigitalStorage() = default;
  virtual void OpenMedia() = 0;
  virtual void FirstFile() = 0;
  virtual NextFileResult NextFile(FileName& name) = 0;
  virtual void OpenFile(FileName name) = 0;
  virtual void SeekPointInFile(uint32_t position) = 0;
  virtual void ReadFile(FileData& data, size_t bytes_to_read, size_t& bytes_received) = 0;
  virtual void CloseFile() = 0;
};
}
