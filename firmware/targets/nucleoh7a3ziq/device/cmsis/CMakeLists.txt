set(NAME device.cmsis)

set(CMSIS_INCLUDES
    ./device/st/stm32h7xx/include
    ./include
)

add_library(device.cmsis INTERFACE)
target_include_directories(${NAME} INTERFACE
 .
 ${CMSIS_INCLUDES}
)