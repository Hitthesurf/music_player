# Add subdirectories
# selects correct target

# If statement to select unit tests for correct target
add_subdirectory(targets/stm32h7xx)

set(NAME device.drivers)

add_library(${NAME} INTERFACE)
target_link_libraries(${NAME} INTERFACE
    mock.drivers.stm32h7a3xxq # if statement
)