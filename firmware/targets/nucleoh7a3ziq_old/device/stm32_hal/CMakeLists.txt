set(NAME device.stm32_hal)

set(STM32HAL_INCLUDES
    inc
    inc/legacy
)

set(STM32HAL_SOURCES
    src/stm32h7xx_hal.c
    src/stm32h7xx_hal_cortex.c
    src/stm32h7xx_hal_dma.c
    src/stm32h7xx_hal_dma_ex.c
    src/stm32h7xx_hal_exti.c
    src/stm32h7xx_hal_flash.c
    src/stm32h7xx_hal_flash_ex.c
    src/stm32h7xx_hal_gpio.c
    src/stm32h7xx_hal_hsem.c
    src/stm32h7xx_hal_i2c.c
    src/stm32h7xx_hal_i2c_ex.c
    src/stm32h7xx_hal_mdma.c
    src/stm32h7xx_hal_pwr.c
    src/stm32h7xx_hal_pwr_ex.c
    src/stm32h7xx_hal_rcc.c
    src/stm32h7xx_hal_rcc_ex.c
    src/stm32h7xx_hal_sd.c
    src/stm32h7xx_hal_sd_ex.c
    src/stm32h7xx_hal_spi.c
    src/stm32h7xx_hal_spi_ex.c
    src/stm32h7xx_hal_tim.c
    src/stm32h7xx_hal_tim_ex.c
    src/stm32h7xx_hal_uart.c
    src/stm32h7xx_hal_uart_ex.c
    src/stm32h7xx_ll_delayblock.c
    src/stm32h7xx_ll_sdmmc.c
)

add_library(${NAME} STATIC ${STM32HAL_SOURCES})
target_include_directories(${NAME} PUBLIC
 .
 ${STM32HAL_INCLUDES}
)
target_link_libraries(${NAME} device.cmsis)