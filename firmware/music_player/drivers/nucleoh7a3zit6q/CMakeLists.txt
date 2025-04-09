set(NAME music_player.drivers)

set(SOURCES led/led_one_driver.cpp)

add_library(${NAME} STATIC ${SOURCES})
target_include_directories(${NAME} PUBLIC .)
target_link_libraries(${NAME} PUBLIC driver.interfaces device.drivers)
