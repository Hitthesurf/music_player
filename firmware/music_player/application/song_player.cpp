#include "song_player.h"
#include "hal_handles.h"
#include "waveforms/waves.h"

using namespace ::application;

SongPlayer::SongPlayer(drivers::ISongDriver& song_driver, IReadMusic& read_music) :
  m_song_driver(song_driver),
  m_read_music(read_music)
{
}

void SongPlayer::NextNote()
{
  m_song_driver.LoadLeft(darkstar_waveform.at(m_note_count));
  m_song_driver.LoadRight(darkstar_waveform.at(m_note_count));
  m_note_count = (m_note_count + 1) % darkstar_count;
}

void SongPlayer::Play() const
{
  m_song_driver.Play();
}

void SongPlayer::Pause() const
{
  m_song_driver.Stop();
}

void SongPlayer::SelectSong(threads::FileName& name)
{
  m_file_name = name;
  m_change_song = true;
}

void SongPlayer::RunStreamThreadTask()
{
  if (m_change_song)
  {
    m_read_music.ReadInfo(m_file_name);
    m_song_driver.Config(m_read_music.GetSampleRate());
    m_change_song = false;
  }
}

void SongPlayer::TimerLoadAudioPeriodElapsedCallback()
{
  this->NextNote();
}
