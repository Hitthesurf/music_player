#pragma once

#include "command_line_interface/defines.h"
#include "command_line_interface/i_command.h"
#include "i_song_player.h"
#include "queue/i_char_queue.h"

namespace application::commands
{

class Play : public ICommand
{
public:
  Play(application::ISongPlayer& song_player, threads::ICharQueue& char_output_queue);

  void Execute() const override;
  std::array<char, KeywordSize> GetKeyword() const override;

private:
  const std::array<char, KeywordSize> m_keyword = {'p', 'l', 'a', 'y', '\n'};
  application::ISongPlayer& m_song_player;
  threads::ICharQueue& m_char_output_queue;
};
}
