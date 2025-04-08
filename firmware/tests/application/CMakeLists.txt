set(NAME tests.application)

set(SOURCES
  tests_led_service.cpp
  tests_command_line_interface.cpp
)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PRIVATE .)
target_link_libraries(${NAME} PRIVATE
  gmock_main
  music_player.application
  tests.mocks
)

add_test(${NAME} ${NAME})