set(NAME mocks.cmsis)
add_library(${NAME} STATIC mock_cmsis.cpp)
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC mock.drivers.stm32)