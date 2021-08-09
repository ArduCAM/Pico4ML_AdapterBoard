#include "command_responder.h"

#include <stdio.h>
#include "LCD_st7735.h"
#include "pico/stdlib.h"

#define LED_PIN 25

// The default implementation writes out the name of the recognized command
// to the error console. Real applications will want to take some custom
// action instead, and should implement their own versions of this function.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {

  // led settings
  static bool is_initialized = false;
  //const uint LED_PIN = 25;
  // if not initialized, setup
  if(!is_initialized) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    is_initialized = true;
  }

  if (is_new_command) {
    TF_LITE_REPORT_ERROR(error_reporter, "Heard %s (%d) @%dms", found_command,
                         score, current_time);

    if (found_command == "yes"){
      ST7735_FillRectangle(0, 30, ST7735_HEIGHT, 40, ST7735_GREEN);
      ST7735_WriteString(25, 30, found_command, Font_11x18, ST7735_BLACK, ST7735_GREEN);
    }
    else if (found_command == "no") {
      ST7735_FillRectangle(0, 30, ST7735_HEIGHT, 40, ST7735_GREEN);
      ST7735_WriteString(30, 30, found_command, Font_11x18, ST7735_BLACK, ST7735_GREEN);
    }
    else{
      ST7735_FillRectangle(0, 30, ST7735_HEIGHT, 40, ST7735_GREEN);
      ST7735_WriteString(1, 30, found_command, Font_11x18, ST7735_BLACK, ST7735_GREEN);
    }
  }
}
