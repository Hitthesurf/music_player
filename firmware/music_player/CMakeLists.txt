add_subdirectory(application)
add_subdirectory(driver_interfaces)
add_subdirectory(drivers/nucleoh7a3zit6q)
add_subdirectory(thread_interfaces)

if (NOT TESTS)
    add_subdirectory(threads)
endif()
