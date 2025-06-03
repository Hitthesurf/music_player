#include "song_player.h"
#include "hal_handles.h"
#include "waveforms/waves.h"

using namespace ::application;

SongPlayer::SongPlayer(drivers::ISongDriver& song_driver, IReadMusic& read_music,
  application::ISamplesQueue& samples_queue) :
  m_song_driver(song_driver),
  m_read_music(read_music),
  m_samples_queue(samples_queue),
  m_current_samples(m_empty_sample)
{
}

void SongPlayer::NextNote()
{
  if (m_note_count == 0)
  {
    m_current_samples = m_samples_queue.GetISR();
  }
  m_song_driver.LoadLeft(m_current_samples.left.at(m_note_count));
  m_song_driver.LoadRight(m_current_samples.right.at(m_note_count));
  m_note_count = (m_note_count + 1) % m_current_samples.sample_count;
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

  StereoSamples& samples = m_samples_queue.AddSampleLocation();
  m_read_music.ProcessData(samples);
  m_samples_queue.AddSampleStored();
}

void SongPlayer::TimerLoadAudioPeriodElapsedCallback()
{
  this->NextNote();
}
