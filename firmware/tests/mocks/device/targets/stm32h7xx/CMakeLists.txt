set(NAME mock.drivers.stm32)

add_library(${NAME} INTERFACE)
target_include_directories(${NAME} INTERFACE .)
