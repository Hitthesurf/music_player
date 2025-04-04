# GoogleTest
include(FetchContent)
fetchcontent_declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e39786088138f2749d64e9e90e0f9902daa77c40 # V1.15.0 - 15/07/2024
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
fetchcontent_makeavailable(googletest)


add_subdirectory(firmware/music_player)

enable_testing()
set(CTEST_OUTPUT_ON_FAILURE ON)
add_subdirectory(firmware/tests)