#include "command_line_interface/commands/play.h"

using namespace ::application::commands;
using namespace ::application;
using namespace ::threads;

Play::Play(ISongPlayer& song_player, ICharQueue& char_output_queue) :
  m_song_player(song_player),
  m_char_output_queue(char_output_queue)
{
}

void Play::Execute() const
{
  m_song_player.Play();
  m_char_output_queue.Add('p');
  m_char_output_queue.Add('l');
  m_char_output_queue.Add('a');
  m_char_output_queue.Add('y');
  m_char_output_queue.Add('\n');
}

std::array<char, KeywordSize> Play::GetKeyword() const
{
  return m_keyword;
}
