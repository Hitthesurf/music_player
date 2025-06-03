#pragma once

#include "read_music/defines.h"

namespace application
{

class ISamplesQueue
{
public:
  virtual ~ISamplesQueue() = default;

  virtual StereoSamples& AddSampleLocation() = 0;
  virtual void AddSampleStored() = 0;
  virtual StereoSamples& GetISR() = 0;
};

}
