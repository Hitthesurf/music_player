# GNU-ARM toolchain initialization

# Target platform
set(CMAKE_SYSTEM_NAME Generic CACHE STRING "System name" FORCE)
set(CMAKE_SYSTEM_VERSION 1 CACHE STRING "System version" FORCE)
set(CMAKE_SYSTEM_PROCESSOR arm CACHE STRING "System processor" FORCE)

# Resolve path to toolchain
if("${TOOLCHAIN_ROOT}" STREQUAL "")
  if(NOT "$ENV{STM32CLT_PATH}" STREQUAL "")
    message(STATUS ">>> TOOLCHAIN_ROOT NOT SET, USING ENV STM32CLT_PATH=$ENV{STM32CLT_PATH}")
    set(TOOLCHAIN_ROOT "$ENV{STM32CLT_PATH}/GNU-tools-for-STM32")
  elseif(NOT "$ENV{GNUARM_PATH}" STREQUAL "")
    message(STATUS ">>> TOOLCHAIN_ROOT NOT SET, USING ENV GNUARM_PATH=$ENV{GNUARM_PATH}")
    set(TOOLCHAIN_ROOT "$ENV{GNUARM_PATH}")
  endif()
endif()

if(NOT "${TOOLCHAIN_ROOT}" STREQUAL "")
  # Convert to an absolute path
  get_filename_component(TOOLCHAIN_ROOT ${TOOLCHAIN_ROOT} ABSOLUTE)
else()
  # TOOLCHAIN_ROOT not given - try to find it from the environment path settings
  find_program(GCC_PATH arm-none-eabi-gcc)
  if(NOT GCC_PATH STREQUAL GCC_PATH-NOTFOUND)
    # Get the root from the found gcc executable
    string(REGEX REPLACE "(.*)/bin/arm-none-eabi-gcc(\\.exe)?" "\\1" TOOLCHAIN_ROOT ${GCC_PATH})
  else()
    message(FATAL_ERROR ">>> GNU-ARM toolchain not found!")
  endif()
endif()

message(STATUS ">>> TOOLCHAIN_ROOT=${TOOLCHAIN_ROOT}")

# Add windows .exe extension
if(WIN32)
  set(EXT ".exe")
endif()

# Toolchain executables
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-gcc${EXT} CACHE STRING "Assembler" FORCE)
set(CMAKE_C_COMPILER ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-gcc${EXT} CACHE STRING "C compiler" FORCE)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-g++${EXT} CACHE STRING "C++ compiler" FORCE)
set(CMAKE_AR ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-gcc-ar${EXT} CACHE STRING "AR" FORCE)
set(CMAKE_OBJCOPY ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-objcopy${EXT} CACHE STRING "OBJCOPY" FORCE)
set(CMAKE_OBJDUMP ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-objdump${EXT} CACHE STRING "OBJDUMP" FORCE)
set(CMAKE_NM ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-gcc-nm${EXT} CACHE STRING "NM" FORCE)
set(CMAKE_RANLIB ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-gcc-ranlib${EXT} CACHE STRING "RANLIB" FORCE)
set(CMAKE_SIZE ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-size${EXT} CACHE STRING "SIZE" FORCE)
set(CMAKE_SIZE_UTIL ${TOOLCHAIN_ROOT}/bin/arm-none-eabi-size${EXT} CACHE INTERNAL "size tool")

# Toolchain paths
set(CMAKE_SYSROOT ${TOOLCHAIN_ROOT}/arm-none-eabi CACHE STRING "SYSROOT" FORCE)
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_ROOT} CACHE STRING "FIND_ROOT" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER CACHE STRING "FIND_ROOT_PROGRAM" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY CACHE STRING "FIND_ROOT_INCLUDE" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY CACHE STRING "FIND_ROOT_PACKAGE" FORCE)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY CACHE STRING "FIND_ROOT_LIBRARY" FORCE)

# Workaround to allow CMake to correctly probe the toolchain (error: "The C compiler ... is not able to compile a simple test program.")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY CACHE STRING "TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY" FORCE)
