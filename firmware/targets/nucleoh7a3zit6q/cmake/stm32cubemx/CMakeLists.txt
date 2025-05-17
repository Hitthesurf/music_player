cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_PWR_DIRECT_SMPS_SUPPLY 
	TX_INCLUDE_USER_DEFINE_FILE 
	USE_HAL_DRIVER 
	STM32H7A3xxQ
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ../../Core/Inc
    ../../AZURE_RTOS/App
    ../../Drivers/STM32H7xx_HAL_Driver/Inc
    ../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ../../Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ../../Drivers/CMSIS/Include
    ../../Middlewares/ST/threadx/common/inc/
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/inc/
    ../../Middlewares/ST/threadx/utility/low_power/
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ../../AZURE_RTOS/App/app_azure_rtos.c
    ../../Core/Src/tx_initialize_low_level.S
    ../../Core/Src/main.c
    ../../Core/Src/app_threadx.c
    ../../Core/Src/stm32h7xx_it.c
    ../../Core/Src/stm32h7xx_hal_msp.c
    ../../Core/Src/stm32h7xx_hal_timebase_tim.c
    ../../Core/Src/sysmem.c
    ../../Core/Src/syscalls.c
    ../../startup_stm32h7a3xxq.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ../../Core/Src/system_stm32h7xx.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ../../Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
)

# Drivers Midllewares


set(ThreadX_Src
    ../../Middlewares/ST/threadx/utility/low_power/tx_low_power.c
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_context_restore.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_context_save.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_interrupt_control.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_interrupt_disable.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_interrupt_restore.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_schedule.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_stack_build.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_thread_system_return.S
    ../../Middlewares/ST/threadx/ports/cortex_m7/gnu/src/tx_timer_interrupt.S
    ../../Middlewares/ST/threadx/common/src/tx_initialize_high_level.c
    ../../Middlewares/ST/threadx/common/src/tx_initialize_kernel_enter.c
    ../../Middlewares/ST/threadx/common/src/tx_initialize_kernel_setup.c
    ../../Middlewares/ST/threadx/common/src/tx_block_allocate.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_create.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_block_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_block_release.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_allocate.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_create.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_pool_search.c
    ../../Middlewares/ST/threadx/common/src/tx_byte_release.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_create.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_get.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_set.c
    ../../Middlewares/ST/threadx/common/src/tx_event_flags_set_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_create.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_get.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_priority_change.c
    ../../Middlewares/ST/threadx/common/src/tx_mutex_put.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_create.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_flush.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_front_send.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_receive.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_send.c
    ../../Middlewares/ST/threadx/common/src/tx_queue_send_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_ceiling_put.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_cleanup.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_create.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_get.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_prioritize.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_put.c
    ../../Middlewares/ST/threadx/common/src/tx_semaphore_put_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_create.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_entry_exit_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_identify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_preemption_change.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_priority_change.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_relinquish.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_reset.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_resume.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_shell_entry.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_sleep.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_stack_analyze.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_stack_error_handler.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_stack_error_notify.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_suspend.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_system_preempt_check.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_system_resume.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_system_suspend.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_terminate.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_time_slice.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_time_slice_change.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_timeout.c
    ../../Middlewares/ST/threadx/common/src/tx_thread_wait_abort.c
    ../../Middlewares/ST/threadx/common/src/tx_time_get.c
    ../../Middlewares/ST/threadx/common/src/tx_time_set.c
    ../../Middlewares/ST/threadx/common/src/txe_block_allocate.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_create.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_block_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_block_release.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_allocate.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_create.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_pool_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_byte_release.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_create.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_get.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_set.c
    ../../Middlewares/ST/threadx/common/src/txe_event_flags_set_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_create.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_get.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_mutex_put.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_create.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_flush.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_front_send.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_receive.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_send.c
    ../../Middlewares/ST/threadx/common/src/txe_queue_send_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_ceiling_put.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_create.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_get.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_prioritize.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_put.c
    ../../Middlewares/ST/threadx/common/src/txe_semaphore_put_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_create.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_entry_exit_notify.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_info_get.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_preemption_change.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_priority_change.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_relinquish.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_reset.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_resume.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_suspend.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_terminate.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_time_slice_change.c
    ../../Middlewares/ST/threadx/common/src/txe_thread_wait_abort.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_activate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_change.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_create.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_deactivate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_delete.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_expiration_process.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_info_get.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_initialize.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_system_activate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_system_deactivate.c
    ../../Middlewares/ST/threadx/common/src/tx_timer_thread_entry.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_activate.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_change.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_create.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_deactivate.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_delete.c
    ../../Middlewares/ST/threadx/common/src/txe_timer_info_get.c
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS 
    STM32_Drivers
    ThreadX
	
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Create ThreadX static library
add_library(ThreadX OBJECT)
target_sources(ThreadX PRIVATE ${ThreadX_Src})
target_link_libraries(ThreadX PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
