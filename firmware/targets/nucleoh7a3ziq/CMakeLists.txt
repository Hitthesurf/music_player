set(NAME nucleoh7a3ziq.elf)

add_subdirectory(device/cmsis)
add_subdirectory(device/stm32_hal)

set(TARGET_SOURCES
    device/startup_stm32h7a3zitxq.s
    device/syscalls.c
    device/sysmem.c
    device/system_stm32h7xx.c
    init.cpp
    main.cpp
)

add_executable(${NAME} ${TARGET_SOURCES})
target_include_directories(${NAME} PRIVATE
 .
)

target_link_libraries(${NAME} 
device.stm32_hal
music_player.application
thread.interfaces
-T\"${CMAKE_CURRENT_SOURCE_DIR}/device/STM32H7A3ZITXQ_FLASH.ld\"
)