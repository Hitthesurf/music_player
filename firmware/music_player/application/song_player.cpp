#include "song_player.h"
#include "hal_handles.h"
#include "waveforms/waves.h"

using namespace ::application;

static SongPlayer* s_song_player = nullptr;

SongPlayer::SongPlayer(drivers::ISongDriver& song_driver) :
  m_song_driver(song_driver)
{
  s_song_player = this;
}

void SongPlayer::NextNote()
{
  m_song_driver.LoadLeft(darkstar_waveform[m_note_count]);
  m_song_driver.LoadRight(darkstar_waveform[m_note_count]);
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

// Timer trigger to load new note
void TimerLoadAudioPeriodElapsedCallback()
{
  s_song_player->NextNote();
}
