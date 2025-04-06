# GNU-ARM toolchain initialization

# Target platform
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Add windows .exe extension
if(WIN32)
  set(EXT ".exe")
endif()

# Toolchain executables
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc${EXT})
set(CMAKE_C_COMPILER arm-none-eabi-gcc${EXT})
set(CMAKE_CXX_COMPILER arm-none-eabi-g++${EXT})
set(CMAKE_AR arm-none-eabi-gcc-ar${EXT})
set(CMAKE_OBJCOPY arm-none-eabi-objcopy${EXT})
set(CMAKE_OBJDUMP arm-none-eabi-objdump${EXT})
set(CMAKE_NM arm-none-eabi-gcc-nm${EXT})
set(CMAKE_RANLIB arm-none-eabi-gcc-ranlib${EXT})
set(CMAKE_SIZE arm-none-eabi-size${EXT})
set(CMAKE_SIZE_UTIL arm-none-eabi-size${EXT})

# Workaround to allow CMake to correctly probe the toolchain (error: "The C compiler ... is not able to compile a simple test program.")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
