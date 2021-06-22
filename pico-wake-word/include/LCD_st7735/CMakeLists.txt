
aux_source_directory(. DIR_LCD_SRCS)


add_library(LCD_st7735 ${DIR_LCD_SRCS})
target_link_libraries(LCD_st7735 PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm)
