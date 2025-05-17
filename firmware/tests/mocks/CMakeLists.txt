add_subdirectory(device)
add_subdirectory(threads/stubs)

set(NAME tests.mocks)

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE .)
target_link_libraries(${NAME} INTERFACE 
music_player.application
)
