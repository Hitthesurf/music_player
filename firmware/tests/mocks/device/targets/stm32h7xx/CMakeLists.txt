set(NAME mock.drivers.stm32)

add_library(${NAME} STATIC stm32h7a3xx_gpio.cpp)
target_include_directories(${NAME} PUBLIC .)
