#include "DEV_Config.h"
#include "st7735.h"
#include <stdio.h>
#include <stdlib.h>

void setup() {
  Serial.begin(9600);
  Serial.print(F("Hello! ST7735 TFT Test"));
  ST7735_Init();
  Serial.println(F("Initialized"));
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
  delay(1000);
  ST7735_FillScreen(ST7735_BLACK);
  delay(1000);
  testlines(ST7735_GREEN);
  delay(1000);
  testlines(ST7735_YELLOW);
  delay(1000);
  testlines(ST7735_BLUE);
  delay(1000);
  testlines(ST7735_RED);
  delay(1000);
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
}

void loop() {
  delay(100);
}

void testlines(uint16_t color) {
  ST7735_FillScreen(ST7735_BLACK);
  for (int16_t x = 0; x < ST7735_WIDTH; x ++) {
    for (int16_t x)
    ST7735_FillRectangle(0, 0, x, ST7735_HEIGHT - 1, color);
  }

}
