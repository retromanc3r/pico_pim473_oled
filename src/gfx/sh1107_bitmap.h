#ifndef SH1107_BITMAP_H
#define SH1107_BITMAP_H
#include "pico/stdlib.h"

#define SMILEY_WIDTH 32
#define SMILEY_HEIGHT 32

// Function to draw a bitmap at a specified location
void sh1107_draw_bitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t w, uint8_t h);

// Smiley face bitmap
extern const unsigned char smiley_bitmap[];

#endif // SH1107_BITMAP_H