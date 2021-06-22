cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(Pico_ePaper_Code)
pico_sdk_init()


add_subdirectory(lib/Config)
add_subdirectory(lib/LCD)
add_subdirectory(lib/icm20948)
add_subdirectory(lib/arducam)




include_directories(./lib/Config)
include_directories(./lib/LCD)
include_directories(./lib/icm20948)
include_directories(./lib/arducam)


add_executable(main 
main.c
)


pico_add_extra_outputs(main)

target_link_libraries(main LCD icm20948 arducam Config  hardware_spi hardware_pio pico_stdlib)