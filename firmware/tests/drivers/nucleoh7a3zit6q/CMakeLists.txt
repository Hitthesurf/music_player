set(NAME tests.drivers)

set(SOURCES
  tests_led_one_driver.cpp
  tests_led_two_driver.cpp
)

add_executable(${NAME} ${SOURCES})
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC
  gmock_main
  music_player.drivers
  tests.mocks
)

add_test(${NAME} ${NAME})