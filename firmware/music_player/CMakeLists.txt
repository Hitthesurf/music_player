add_subdirectory(application)
add_subdirectory(driver_interfaces)
add_subdirectory(drivers)
add_subdirectory(thread_interfaces)

if (NOT TESTS)
    add_subdirectory(threads)
endif()
