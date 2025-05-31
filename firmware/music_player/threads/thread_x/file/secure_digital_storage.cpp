#include "file/secure_digital_storage.h"
#include "fx_api.h"

using namespace ::threads;

void SecureDigitalStorage::OpenMedia()
{
  UINT sd_status = FX_SUCCESS;
  sd_status = fx_media_open(&m_sdio_disk, (CHAR*)"Bob", fx_stm32_sd_driver, (VOID*)FX_NULL, (VOID*)m_fx_sd_media_memory,
    sizeof(m_fx_sd_media_memory));
  if (sd_status != FX_SUCCESS)
  {
    for (;;)
    {
    }
  }
}

void SecureDigitalStorage::FirstFile()
{
  m_first_file = true;
}

NextFileResult SecureDigitalStorage::NextFile(FileName& name)
{
  UINT sd_status = FX_SUCCESS;
  UINT attributes;
  ULONG size;
  UINT year, month, day, hour, minute, second;
  if (m_first_file)
  {
    sd_status = fx_directory_first_full_entry_find(&m_sdio_disk, name.data(), &attributes, &size, &year, &month, &day,
      &hour, &minute, &second);
    m_first_file = false;
  }
  else
  {
    sd_status = fx_directory_next_full_entry_find(&m_sdio_disk, name.data(), &attributes, &size, &year, &month, &day,
      &hour, &minute, &second);
  }
  return (sd_status == FX_SUCCESS) ? NextFileResult::FileFound : NextFileResult::NoFileFound;
}

void SecureDigitalStorage::OpenFile(FileName name) {}

void SecureDigitalStorage::ReadFile(FileData& data, size_t& data_size) {}

void SecureDigitalStorage::CloseFile() {}
