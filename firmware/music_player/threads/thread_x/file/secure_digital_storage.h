#pragma once
#include "file/i_secure_digital_storage.h"
#include "fx_api.h"
#include "fx_stm32_sd_driver.h"

namespace threads
{
class SecureDigitalStorage : public ISecureDigitalStorage
{
public:
  SecureDigitalStorage() = default;
  void OpenMedia() override;
  void FirstFile() override;
  NextFileResult NextFile(FileName& name) override;
  void OpenFile(FileName name) override;
  void SeekPointInFile(uint32_t position) override;
  void ReadFile(FileData& data, size_t bytes_to_read, size_t& bytes_received) override;
  void CloseFile() override;

private:
  ALIGN_32BYTES(uint32_t m_fx_sd_media_memory[FX_STM32_SD_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)]);
  bool m_first_file = true;
  bool m_media_open = false;
  FX_MEDIA m_sdio_disk;
  FX_FILE m_fx_file;
};
}
