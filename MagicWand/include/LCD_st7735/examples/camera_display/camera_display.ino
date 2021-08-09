#include "LCD_st7735.h"
#include "arducam_hm01b0.h"

uint8_t image_data[96 * 96];
struct arducam_config config;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  ST7735_Init();
  ST7735_DrawImage(0, 0, 80, 160, arducam_logo);
  sleep_ms(1000);

  // put your setup code here, to run once:
  config.sccb = i2c0;
  config.sccb_mode = I2C_MODE_16_8;
  config.sensor_address = 0x24;
  config.pin_sioc = PIN_CAM_SIOC;
  config.pin_siod = PIN_CAM_SIOD;
  config.pin_resetb = PIN_CAM_RESETB;
  config.pin_xclk = PIN_CAM_XCLK;
  config.pin_vsync = PIN_CAM_VSYNC;
  config.pin_y2_pio_base = PIN_CAM_Y2_PIO_BASE;
  config.pio = pio0;
  config.pio_sm = 0;
  config.dma_channel = 0;
  arducam_init(&config);

  ST7735_FillScreen(ST7735_BLACK);
}

void loop() {
  digitalWrite(LED_BUILTIN,
               HIGH); // turn the LED on (HIGH is the voltage level)

  arducam_capture_frame(&config, (uint8_t *)image_data);
  uint8_t *displayBuf = new uint8_t[96 * 96 * 2];
  uint16_t index = 0;
  for (int x = 0; x < 96 * 96; x++) {
    uint16_t imageRGB =
        ST7735_COLOR565(image_data[x], image_data[x], image_data[x]);
    displayBuf[index++] = (uint8_t)(imageRGB >> 8) & 0xFF;
    displayBuf[index++] = (uint8_t)(imageRGB)&0xFF;
  }
  ST7735_DrawImage(0, 0, 96, 96, displayBuf);
  delete[] displayBuf;

  digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
}
