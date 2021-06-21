aux_source_directory(. DIR_icm20948_SRCS)

add_library(icm20948 ${DIR_icm20948_SRCS})
target_link_libraries(icm20948 PUBLIC hardware_i2c pico_stdlib)

