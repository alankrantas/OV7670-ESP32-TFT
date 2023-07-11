// Display live video from OV7670 (without FIFO) on 320x320 ILI9341 TFT with ESP32
// based on https://github.com/kobatan/OV7670-ESP32

#include <Wire.h>
#include <SPI.h>
#include <OV7670.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define MODE      QVGA  // 320 X 240
//#define MODE      QQVGA  // 160 x 120
//#define MODE      QCIF  // 176 x 144 (crop)
//#define MODE      QQCIF  //  88 x 72 (crop)

#define COLOR     RGB565
//#define COLOR     YUV422

#define ROTATION  1  // 0~4

// TFT pins
#define TFT_DC 		16
#define TFT_CS 		 5
#define TFT_RST 	17
#define TFT_MISO 	19
#define TFT_MOSI 	23
#define TFT_CLK 	18

// OV7670 pins
const camera_config_t cam_conf = {
  .D0	   = 36,
  .D1    = 39,
  .D2    = 34,
  .D3    = 35,
  .D4    = 32,
  .D5    = 33,
  .D6    = 25,
  .D7    = 26,
  .XCLK  = 27,
  .PCLK  = 14,
  .VSYNC = 13,
  .xclk_freq_hz = 10000000,   // XCLK 10MHz
  .ledc_timer		= LEDC_TIMER_0,
  .ledc_channel = LEDC_CHANNEL_0
};
// SSCB_SDA(SIOD) -> 21(ESP32)
// SSCB_SCL(SIOC) -> 22(ESP32)
// RESET          -> 3.3V
// PWDN		        -> GND
// HREF		        -> NC

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
OV7670 cam;
uint16_t *buf, w, h;

void setup() {

  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  tft.begin();
  tft.setRotation(ROTATION);
  tft.fillScreen(0);

  esp_err_t err = cam.init(&cam_conf, MODE, COLOR);
  if (err != ESP_OK) Serial.println("cam.init ERROR");

  cam.setPCLK(2, DBLV_CLK_x4);
  cam.vflip(false);
  Serial.printf("cam MID = %X\n\r", cam.getMID());
  Serial.printf("cam PID = %X\n\r", cam.getPID());

  switch (MODE) {
    case QVGA:
      w = 320;
      h = 240;
      break;
    case QQVGA:
      w = 160;
      h = 120;
      break;
    case QCIF:
      w = 176;
      h = 144;
      break;
    case QQCIF:
      w = 88;
      h = 72;
  }

}

void loop(void) {

  for (uint16_t y = 0; y < h; y++) {
    buf = cam.getLine(y + 1);
    tft.drawRGBBitmap(0, y, buf, w, 1);
  }

}
