#pragma once

#include "file/i_secure_digital_storage.h"

namespace threads
{

class SecureDigitalStorage : public ISecureDigitalStorage
{
public:
  SecureDigitalStorage() = default;

  void OpenMedia() override
  {
    // Stub: no implementation needed for tests.
  }

  void FirstFile() override
  {
    // Stub: no implementation needed for tests.
  }

  NextFileResult NextFile(FileName& name) override
  {
    // Stub: return no files found.
    return NextFileResult::NoFileFound;
  }

  void OpenFile(FileName name) override
  {
    // Stub: no implementation needed for tests.
  }

  void SeekPointInFile(uint32_t position) override
  {
    // Stub: no implementation needed for tests.
  }

  void ReadFile(FileData& data, size_t bytes_to_read, size_t& bytes_received) override
  {
    // Stub: no implementation needed for tests.
  }

  void CloseFile() override
  {
    // Stub: no implementation needed for tests.
  }
};

}
