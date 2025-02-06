#ifndef SH1107_DRAW_H
#define SH1107_DRAW_H

#include "pico/stdlib.h"
#include "../driver/sh1107_driver.h"
#include "../fonts/sh1107_font.h"

// Display dimensions
#define OLED_WIDTH 128
#define OLED_HEIGHT 128

// Function to draw a pixel at a specified location
void sh1107_draw_pixel(uint8_t x, uint8_t y, bool color);

// Function to draw a line between two points
void sh1107_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color);

// Function to draw a square at a specified location
void sh1107_draw_square(uint8_t x, uint8_t y, uint8_t size, bool color);

// Function to draw a circle at a specified location
void sh1107_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, bool color);

// Function to draw a bitmap at a specified location
void sh1107_draw_text(uint8_t x, uint8_t y, const char *text, bool color);


#endif // SH1107_DRAW_H
