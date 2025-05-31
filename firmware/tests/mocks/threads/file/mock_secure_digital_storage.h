#pragma once

#include "file/i_secure_digital_storage.h"
#include <queue>

namespace tests
{

class MockSecureDigitalStorage : public threads::ISecureDigitalStorage
{
public:
  void OpenMedia() override
  {
    state.open_media_call_count++;
  }

  void FirstFile() override
  {
    state.first_file_call_count++;
  }

  threads::NextFileResult NextFile(threads::FileName& name) override
  {
    state.next_file_call_count++;
    name = state.next_file_name.front();
    state.next_file_name.pop();
    return state.next_file_return_value;
  }

  void OpenFile(threads::FileName name) override
  {
    state.open_file_call_count++;
    state.open_file_name.push(name);
  }

  void SeekPointInFile(uint32_t position) override
  {
    state.seek_point_call_count++;
    state.last_seek_position = position;
  }

  void ReadFile(threads::FileData& data, size_t& data_size) override
  {
    state.read_file_call_count++;
    data = state.read_file_data.front();
    data_size = state.read_file_data_size.front();
    state.read_file_data.pop();
    state.read_file_data_size.pop();
  }

  void CloseFile() override
  {
    state.close_file_call_count++;
  }

  struct StateType
  {
    size_t open_media_call_count = 0;

    size_t first_file_call_count = 0;

    size_t next_file_call_count = 0;
    std::queue<threads::FileName> next_file_name{};
    threads::NextFileResult next_file_return_value = threads::NextFileResult::NoFileFound;

    size_t open_file_call_count = 0;
    std::queue<threads::FileName> open_file_name{};

    size_t seek_point_call_count = 0;
    uint32_t last_seek_position = 0;

    size_t read_file_call_count = 0;
    std::queue<size_t> read_file_data_size{};

    size_t close_file_call_count = 0;

    std::queue<threads::FileData> read_file_data{};
  } mutable state{};
};

}
