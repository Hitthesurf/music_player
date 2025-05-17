set(NAME threads)

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE .)
target_link_libraries(${NAME} INTERFACE
    thread.interfaces
)