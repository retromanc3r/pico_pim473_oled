#ifndef SH1107_DRIVER_H
#define SH1107_DRIVER_H

#include "../fonts/sh1107_font.h"
#include "../gfx/sh1107_draw.h"
#include "../gfx/sh1107_bitmap.h"
#include "hardware/spi.h"
#include "pico/stdlib.h"
#include <string.h>

// SPI port and pins
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_RES  15

// SPI speed
#define SPI_SPEED 1000000

// SH110X Command Definitions (from Adafruit SH110X.h)
#define SH110X_MEMORYMODE 0x20
#define SH110X_COLUMNADDR 0x21
#define SH110X_PAGEADDR 0x22
#define SH110X_SETCONTRAST 0x81
#define SH110X_CHARGEPUMP 0x8D
#define SH110X_SEGREMAP 0xA0
#define SH110X_DISPLAYALLON_RESUME 0xA4
#define SH110X_DISPLAYALLON 0xA5
#define SH110X_NORMALDISPLAY 0xA6
#define SH110X_INVERTDISPLAY 0xA7
#define SH110X_SETMULTIPLEX 0xA8
#define SH110X_DCDC 0xAD
#define SH110X_DISPLAYOFF 0xAE
#define SH110X_DISPLAYON 0xAF
#define SH110X_SETPAGEADDR 0xB0
#define SH110X_COMSCANINC 0xC0
#define SH110X_COMSCANDEC 0xC8
#define SH110X_SETDISPLAYOFFSET 0xD3
#define SH110X_SETDISPLAYCLOCKDIV 0xD5
#define SH110X_SETPRECHARGE 0xD9
#define SH110X_SETCOMPINS 0xDA
#define SH110X_SETVCOMDETECT 0xDB
#define SH110X_SETDISPSTARTLINE 0xDC
#define SH110X_SETLOWCOLUMN 0x00
#define SH110X_SETHIGHCOLUMN 0x10
#define SH110X_SETSTARTLINE 0x40

// Display buffer (128x128 / 8) = 2048 bytes (1 bit per pixel)
extern uint8_t display_buffer[2048];  // 128x128 / 8

// Function prototypes
void spi_init_display();
void sh1107_send_command(uint8_t command);
void sh1107_send_data(uint8_t *data, size_t len);
void sh1107_update_display();
void sh1107_clear_buffer();
void sh1107_clear_display();
void sh1107_test_fill();
void sh1107_draw_pixel(uint8_t x, uint8_t y, bool color);
void sh1107_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);
void sh1107_draw_square(uint8_t x, uint8_t y, uint8_t size, bool color);
void sh1107_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, bool color);
void sh1107_draw_bitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h);
void sh1107_draw_text(uint8_t x, uint8_t y, const char *text, bool color);
void sh1107_init();

#endif // SH1107_DRIVER_H
