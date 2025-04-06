include(${CMAKE_CURRENT_LIST_DIR}/target_stm32.cmake)

set(TARGET_ARCHITECTURE
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
    --specs=nano.specs
)

# For global effect
add_compile_options(${TARGET_ARCHITECTURE})
add_link_options(${TARGET_ARCHITECTURE})
