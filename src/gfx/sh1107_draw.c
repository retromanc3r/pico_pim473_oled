#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "sh1107_draw.h"

void sh1107_draw_pixel(uint8_t x, uint8_t y, bool color) {
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) {
        return;  // Ignore out-of-bounds pixels
    }

    // 🔥 Flip the Y-axis to start (0,0) at the top-left corner
    y = (OLED_HEIGHT - 1) - y;

    uint16_t index = x + (y / 8) * OLED_WIDTH;  // Correct indexing
    uint8_t bit_position = y % 8;  // Bit in byte (no inversion)

    if (color) {
        display_buffer[index] |= (1 << bit_position);  // Set bit (white pixel)
    } else {
        display_buffer[index] &= ~(1 << bit_position); // Clear bit (black pixel)
    }
}

void sh1107_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy, e2;  // Bresenham's error term

    while (true) {
        sh1107_draw_pixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }  // Move x
        if (e2 <= dx) { err += dx; y0 += sy; }  // Move y
    }
}

void sh1107_draw_square(uint8_t x, uint8_t y, uint8_t size, bool color) {
    uint8_t x1 = x + size - 1, y1 = y + size - 1;

    sh1107_draw_line(x, y, x1, y, color);   // Top edge
    sh1107_draw_line(x1, y, x1, y1, color); // Right edge
    sh1107_draw_line(x1, y1, x, y1, color); // Bottom edge
    sh1107_draw_line(x, y1, x, y, color);   // Left edge

    sh1107_update_display();
    sleep_ms(1000);
    sh1107_clear_display();
}

void sh1107_draw_circle(uint8_t x0, uint8_t y0, uint8_t r, bool color) {
    int16_t x = 0, y = r;
    int16_t d = 3 - (2 * r); // Bresenham's circle algorithm

    while (x <= y) {
        sh1107_draw_pixel(x0 + x, y0 + y, color);
        sh1107_draw_pixel(x0 - x, y0 + y, color);
        sh1107_draw_pixel(x0 + x, y0 - y, color);
        sh1107_draw_pixel(x0 - x, y0 - y, color);
        sh1107_draw_pixel(x0 + y, y0 + x, color);
        sh1107_draw_pixel(x0 - y, y0 + x, color);
        sh1107_draw_pixel(x0 + y, y0 - x, color);
        sh1107_draw_pixel(x0 - y, y0 - x, color);

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    sh1107_update_display();
    sleep_ms(1000);
    sh1107_clear_display();
}

void sh1107_draw_text(uint8_t x, uint8_t y, const char *text, bool color) {
    while (*text) {
        char c = *text;
        if (c < 32 || c > 127) {
            c = 32; // Default to space for unsupported characters
        }

        // Get font data for character
        const uint8_t *char_bitmap = font6x8[c - 32]; // 6x8 character

        for (uint8_t i = 0; i < 6; i++) {  // 6 columns per character
            uint8_t line = char_bitmap[i]; // Get column data
            for (uint8_t j = 0; j < 8; j++) {
                if (line & (1 << j)) {  
                    sh1107_draw_pixel(x + i, y + (7 - j), color);   // Flip vertical pixel order    
                } else {
                    sh1107_draw_pixel(x + i, y + (7 - j), !color);  // Flip vertical pixel order
                }
            }
        }

        x += 6; // Move right for the next character
        text++; // Go to next character
    }

    sh1107_update_display();  // Ensure display refreshes after text is drawn
    sleep_ms(5000);
    sh1107_clear_display();
}
