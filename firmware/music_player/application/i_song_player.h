#pragma once

namespace application
{

class ISongPlayer
{
public:
  virtual ~ISongPlayer() = default;
  virtual void NextNote() = 0;
  virtual void Play() const = 0;
  virtual void Pause() const = 0;
  virtual void TimerLoadAudioPeriodElapsedCallback() = 0;
};

}
