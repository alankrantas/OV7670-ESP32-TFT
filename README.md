# OV7670-ESP32-TFT

Display live color video of a non-FIFO OV7670 camera module on a 320x480 ILI9341 TFT display using a generic ESP32 board.

## Hardware

* ESP32 (ESP32S or ESP32 DevKit V1 will do)
* non-FIFO OV7670 camera module (it dosen't have a big chip underneath the PCB)
* ILI9341 TFT LCD display (320x240) - I used a non-Adafruit one

Note: since most pins are used, there is no room to attach a SD card module or something.

## Drivers

* [OV7670-ESP32](https://github.com/kobatan/OV7670-ESP32) driver by kobatan (download it and manually unzip into the Arduino IDE library directory)
* [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library) and [Adafruit_ILI9341](https://github.com/adafruit/Adafruit_ILI9341)

## Wiring

| OV7670 | ESP32 Pin |
| --- | --- |
| RESET | 3.3V |
| PWDN | GND |
| SSCB_SDA (SIOD) | 21 |
| SSCB_SCL (SIOC) | 22 |
| HREF | NC (not connected) |
| D0 | 36 |
| D1 | 39 |
| D2 | 34 |
| D3 | 35 |
| D4 | 32 |
| D5 | 33 |
| D6 | 25 |
| D7 | 26 |
| XCLK | 27 |
| PCLK | 14 |
| VSYNC | 13 |

| ILI9341 | ESP32 Pin |
| --- | --- |
| VCC | 3.3V |
| GND | GND |
| DC | 16 |
| CS | 5 |
| RST | 17 |
| MISO | 19 |
| MOSI | 23 |
| CLK | 18 |
| LED (backlight) | 3.3V |

## Resolution and Rotation

Change ```ROTATION``` and ```MODE``` definition in the script.

Due to the size of the screen, only the following resolutions are supported:

* QVGA (320X240)
* QQVGA (160x120)
* QCIF (176x144, cropped)
* QQCIF (88x72, cropped)

You can focus the image by spinning the lens' position.
