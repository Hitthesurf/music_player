#pragma once

#include "i_song_driver.h"
#include "i_song_player.h"

namespace application
{
class SongPlayer : public ISongPlayer
{
public:
  SongPlayer(drivers::ISongDriver& song_driver);
  void NextNote() override;
  void Play() const override;
  void Pause() const override;
  void TimerLoadAudioPeriodElapsedCallback() override;

private:
  drivers::ISongDriver& m_song_driver;
  size_t m_note_count = 0;
};
}
