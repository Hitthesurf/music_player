#include "command_line_interface/commands/pause.h"

using namespace ::application::commands;
using namespace ::application;
using namespace ::threads;

Pause::Pause(ISongPlayer& song_player, ICharQueue& char_output_queue) :
  m_song_player(song_player),
  m_char_output_queue(char_output_queue)
{
}

void Pause::Execute() const
{
  m_song_player.Pause();
  m_char_output_queue.Add('p');
  m_char_output_queue.Add('a');
  m_char_output_queue.Add('u');
  m_char_output_queue.Add('s');
  m_char_output_queue.Add('e');
  m_char_output_queue.Add('\n');
}

std::array<char, KeywordSize> Pause::GetKeyword() const
{
  return m_keyword;
}
