# GNU-ARM toolchain initialization

# Target platform
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Add windows .exe extension
if(WIN32)
  set(EXT ".exe")
endif()

if(DEFINED ENV{STM32CLT_PATH})
  set(TOOLCHAIN_BASE "$ENV{STM32CLT_PATH}")
elseif(DEFINED ENV{STM32CUBECLT_PATH})
  set(TOOLCHAIN_BASE "$ENV{STM32CUBECLT_PATH}")
else()
  message(FATAL_ERROR "Neither STM32CLT_PATH nor STM32CUBECLT_PATH is defined")
endif()

set(TOOLCHAIN_PATH "${TOOLCHAIN_BASE}/GNU-tools-for-STM32/bin")

# Toolchain executables
set(CMAKE_ASM_COMPILER     "${TOOLCHAIN_PATH}/arm-none-eabi-gcc${EXT}")
set(CMAKE_C_COMPILER       "${TOOLCHAIN_PATH}/arm-none-eabi-gcc${EXT}")
set(CMAKE_CXX_COMPILER     "${TOOLCHAIN_PATH}/arm-none-eabi-g++${EXT}")
set(CMAKE_AR               "${TOOLCHAIN_PATH}/arm-none-eabi-gcc-ar${EXT}")
set(CMAKE_OBJCOPY          "${TOOLCHAIN_PATH}/arm-none-eabi-objcopy${EXT}")
set(CMAKE_OBJDUMP          "${TOOLCHAIN_PATH}/arm-none-eabi-objdump${EXT}")
set(CMAKE_NM               "${TOOLCHAIN_PATH}/arm-none-eabi-gcc-nm${EXT}")
set(CMAKE_RANLIB           "${TOOLCHAIN_PATH}/arm-none-eabi-gcc-ranlib${EXT}")
set(CMAKE_SIZE             "${TOOLCHAIN_PATH}/arm-none-eabi-size${EXT}")
set(CMAKE_SIZE_UTIL        "${TOOLCHAIN_PATH}/arm-none-eabi-size${EXT}")

# Workaround to allow CMake to correctly probe the toolchain (error: "The C compiler ... is not able to compile a simple test program.")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
