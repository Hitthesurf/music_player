# GoogleTest
include(FetchContent)
fetchcontent_declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e39786088138f2749d64e9e90e0f9902daa77c40 # V1.15.0 - 15/07/2024
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
fetchcontent_makeavailable(googletest)

# Has to be enabled after fetching gtest, otherwise runs on gtest
if (CLANG_TIDY)
  set(CMAKE_C_CLANG_TIDY "clang-tidy;--allow-no-checks" CACHE STRING "Enable clang-tidy for C")
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy;--allow-no-checks" CACHE STRING "Enable clang-tidy for C++")
endif()

add_subdirectory(firmware/music_player)

enable_testing()
set(CTEST_OUTPUT_ON_FAILURE ON)
add_subdirectory(firmware/tests)