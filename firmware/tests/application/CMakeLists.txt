set(NAME tests.application)

set(SOURCES
  commands/tests_command_pause.cpp
  commands/tests_command_play.cpp
  tests_char_input.cpp
  tests_char_output.cpp
  tests_command_line_interface.cpp
  tests_commands.cpp
  tests_led_service.cpp
  tests_read_wave.cpp
  tests_song_player.cpp
)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE .)
target_link_libraries(${NAME} PRIVATE
  gmock_main
  music_player.application
  tests.mocks
)

add_test(${NAME} ${NAME})