set(NAME threads)

set(SOURCES
  file/secure_digital_storage.cpp
  queue/char_queue.cpp
  queue/uint8_queue.cpp
  thread_create/thread_create.cpp
  thread_utils.cpp
)

add_library(${NAME} STATIC ${SOURCES})

target_include_directories(${NAME} PUBLIC .)

target_link_libraries(${NAME} PUBLIC
    thread.interfaces
    device.drivers
)
