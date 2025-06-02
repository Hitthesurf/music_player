#pragma once

#include "i_song_driver.h"
#include "i_song_player.h"
#include "read_music/i_read_music.h"

namespace application
{
class SongPlayer : public ISongPlayer
{
public:
  explicit SongPlayer(drivers::ISongDriver& song_driver, application::IReadMusic& read_music);
  void NextNote() override;
  void Play() const override;
  void Pause() const override;
  void SelectSong(threads::FileName& name) override;
  void RunStreamThreadTask() override;
  void TimerLoadAudioPeriodElapsedCallback() override;

private:
  drivers::ISongDriver& m_song_driver;
  application::IReadMusic& m_read_music;
  size_t m_note_count = 0;
  threads::FileName m_file_name;
  bool m_change_song = false;
};
}
