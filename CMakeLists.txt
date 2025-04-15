cmake_minimum_required(VERSION 3.26)
project(music-player CXX C ASM)

option(TESTS "Build unit tests" OFF)

# Export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fail configure if target link library not found
set(CMAKE_LINK_LIBRARIES_ONLY_TARGETS ON)

# Default to Debug if no build type specified
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
endif()

if(TESTS)
  include(firmware/unittests.cmake)
else()
  include(firmware/firmware.cmake)
endif()
