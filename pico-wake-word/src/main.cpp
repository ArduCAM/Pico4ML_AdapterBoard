

#include <stdio.h>

#include "pico/stdlib.h"
#include "tusb.h"
#include "LCD_st7735.h"
#include "main_functions.h"

// This is the default main used on systems that have the standard C entry
// point. Other devices (for example FreeRTOS or ESP32) that have different
// requirements for entry code (like an app_main function) should specialize
// this main.cc file in a target-specific subfolder.
int main(int argc, char* argv[]) {
  stdio_init_all();
  ST7735_Init();
  ST7735_FillScreen(ST7735_GREEN);
  ST7735_WriteString(90, 20,  "Micro", Font_11x18, ST7735_BLACK, ST7735_GREEN);
  ST7735_WriteString(90, 40, "Speech", Font_11x18, ST7735_BLACK, ST7735_GREEN);
  setup();
  while (true) {
    loop();
  }
}
