set(NAME music_player.application)

set(SOURCES
  char_input.cpp
  char_output.cpp
  command_line_interface/command_line_interface.cpp
  command_line_interface/commands/echo.cpp
  command_line_interface/commands/pause.cpp
  command_line_interface/commands/play.cpp
  command_line_interface/commands.cpp
  led/led_service.cpp
  read_music/read_wave.cpp
  read_music/samples_queue.cpp
  setup_thread_tasks.cpp
  song_player.cpp
  waveforms/darkstar.cpp
)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC
    thread.interfaces
    threads
    music_player.drivers
    device.drivers
)