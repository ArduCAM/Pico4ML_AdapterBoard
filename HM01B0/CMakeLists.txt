cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)
project(Pico_ePaper_Code)
pico_sdk_init()

#添加编译子目录
add_subdirectory(lib/Config)
add_subdirectory(lib/LCD)
add_subdirectory(lib/icm20948)
add_subdirectory(lib/arducam)



#添加头文件目录
include_directories(./lib/Config)
include_directories(./lib/LCD)
include_directories(./lib/icm20948)
include_directories(./lib/arducam)

# 生成可执行文件
add_executable(main 
main.c
)

# enable usb output, disable uart output
#pico_enable_stdio_usb(main 1)
#pico_enable_stdio_uart(main 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)

target_link_libraries(main LCD icm20948 arducam Config  hardware_spi hardware_pio pico_stdlib)