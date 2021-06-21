# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_ePaper_SRCS 变量
aux_source_directory(. DIR_LCD_SRCS)

# 生成链接库
add_library(LCD_st7735 ${DIR_LCD_SRCS})
target_link_libraries(LCD_st7735 PUBLIC pico_stdlib hardware_spi hardware_i2c hardware_pwm)
