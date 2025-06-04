#include "file/secure_digital_storage.h"
#include "fx_api.h"

using namespace ::threads;

void SecureDigitalStorage::OpenMedia()
{
  if (m_media_open)
  {
    return;
  }
  UINT sd_status = FX_SUCCESS;
  sd_status = fx_media_open(&m_sdio_disk, (CHAR*)"Bob", fx_stm32_sd_driver, (VOID*)FX_NULL, (VOID*)m_fx_sd_media_memory,
    sizeof(m_fx_sd_media_memory));
  if (sd_status != FX_SUCCESS)
  {
    for (;;)
    {
    }
  }
  m_media_open = true;
}

void SecureDigitalStorage::FirstFile()
{
  m_first_file = true;
}

NextFileResult SecureDigitalStorage::NextFile(FileName& name)
{
  OpenMedia();
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

void SecureDigitalStorage::OpenFile(FileName name)
{
  OpenMedia();
  UINT sd_status = FX_SUCCESS;
  sd_status = fx_file_open(&m_sdio_disk, &m_fx_file, name.data(), FX_OPEN_FOR_READ);
  sd_status = fx_file_seek(&m_fx_file, 0);
}

void SecureDigitalStorage::SeekPointInFile(uint32_t position)
{
  UINT sd_status = FX_SUCCESS;
  sd_status = fx_file_seek(&m_fx_file, position);
}

void SecureDigitalStorage::ReadFile(FileData& data, size_t bytes_to_read, size_t& bytes_received)
{
  ULONG bytes_read = 0;
  UINT sd_status = FX_SUCCESS;
  const size_t data_read_size = max_data_read_size > bytes_to_read ? bytes_to_read : max_data_read_size;
  sd_status = fx_file_read(&m_fx_file, data.data(), data_read_size, &bytes_read);
  bytes_received = bytes_read;
}

void SecureDigitalStorage::CloseFile()
{
  UINT sd_status = FX_SUCCESS;
  sd_status = fx_file_close(&m_fx_file);
}
