#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

set(NAME nucleoh7a3ziq.elf)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ./Core/Inc
    ./Drivers/STM32H7xx_HAL_Driver/Inc
    ./Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ./Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ./Drivers/CMSIS/Include
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ./Core/Src/main.c
    ./Core/Src/stm32h7xx_it.c
    ./Core/Src/stm32h7xx_hal_msp.c
    ./Core/Src/sysmem.c
    ./Core/Src/syscalls.c
    ./startup_stm32h7a3xxq.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ./Core/Src/system_stm32h7xx.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ./Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
)

add_executable(${NAME}
 ${MX_Application_Src}
 ${STM32_Drivers_Src}
)

target_include_directories(${NAME} PRIVATE
${MX_Include_Dirs}
.
)

target_link_libraries(${NAME} 
music_player.application
thread.interfaces
-T\"${CMAKE_CURRENT_SOURCE_DIR}/STM32H7A3XX_FLASH.ld\"
)


