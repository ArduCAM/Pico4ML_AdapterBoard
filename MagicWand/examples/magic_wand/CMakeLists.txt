
cmake_minimum_required(VERSION 3.12)

project(magic_wand C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)







add_executable(pico4ml_ble_magic_wand "")

target_include_directories(pico4ml_ble_magic_wand
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/.
  )

set_target_properties(
  pico4ml_ble_magic_wand
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(pico4ml_ble_magic_wand
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/pico4ml_ble_accelerometer_handler.cpp
  ${CMAKE_CURRENT_LIST_DIR}/gesture_predictor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/magic_wand_model_data.cpp
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/pico4ml_ble_main_functions.cpp
  ${CMAKE_CURRENT_LIST_DIR}/output_handler.cpp
  ${CMAKE_CURRENT_LIST_DIR}/accelerometer_handler.h
  ${CMAKE_CURRENT_LIST_DIR}/constants.h
  ${CMAKE_CURRENT_LIST_DIR}/gesture_predictor.h
  ${CMAKE_CURRENT_LIST_DIR}/magic_wand_model_data.h
  ${CMAKE_CURRENT_LIST_DIR}/main_functions.h
  ${CMAKE_CURRENT_LIST_DIR}/output_handler.h
  )

target_link_libraries(
  pico4ml_ble_magic_wand
  pico-tflmicro
  hardware_pwm
  pico_stdlib
  ICM42622
  LCD_st7735
)

# enable usb output, disable uart output
pico_enable_stdio_usb(pico4ml_ble_magic_wand 1)
pico_enable_stdio_uart(pico4ml_ble_magic_wand 0)

pico_add_extra_outputs(pico4ml_ble_magic_wand)

