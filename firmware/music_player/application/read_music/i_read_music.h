#pragma once

#include "file/defines.h"
#include "read_music/defines.h"
#include <cstdint>

namespace application
{

class IReadMusic
{
public:
  virtual ~IReadMusic() = default;
  virtual void ReadInfo(threads::FileName name) = 0;
  virtual void ProcessData(StereoSamples& stereo_samples) = 0;
  [[nodiscard]]
  virtual uint32_t GetSampleRate() const = 0;
};

}
