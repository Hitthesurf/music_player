set(NAME music_player.application)

set(SOURCES
  app.cpp
  command_line_interface/command_line_interface.cpp
  led/led_service.cpp
)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC
    thread.interfaces
    music_player.drivers
    device.drivers
)