set(NAME music_player.application)

set(SOURCES
  command_line_interface/command_line_interface.cpp
)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC
    thread.interfaces
)