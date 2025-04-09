set(NAME mocks.hal)
add_library(${NAME} STATIC mock_hal.cpp)
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC mock.drivers.stm32)