set(NAME nucleoh7a3ziq.elf)

set(CMSIS_INCLUDES
    device/cmsis/device/st/stm32h7xx/include
    device/cmsis/include
)

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
 ${CMSIS_INCLUDES}
)

target_link_libraries(${NAME} 
music_player.application
thread.interfaces
-T\"${CMAKE_CURRENT_SOURCE_DIR}/device/STM32H7A3ZITXQ_FLASH.ld\"
)