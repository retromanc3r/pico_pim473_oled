#include "driver/sh1107_driver.h"

// SPI port and pins are set in sh1107_driver.h

int main() {
    // Initialize stdio and SPI for the Pico to drive the display
    stdio_init_all();
    // Initialize SPI and display pins for the Pico PIM473
    spi_init_display();
    // Initialize the display and clear the buffer and display
    sh1107_init();
    // Test fill patterns for the display buffer (black/white)
    sh1107_test_fill();
    // Demonstrates drawing a bitmap at different locations
    for (int y = 0; y < 128; y += 32) {
        for (int x = 0; x < 128; x += 32) {
            sh1107_draw_bitmap(x, y, smiley_bitmap, 32, 32);
            sh1107_update_display();
            sleep_ms(100);
            sh1107_clear_display();
        }
    }
    // Draw text and a bitmap in the center of the display
    sh1107_draw_bitmap(50, 32, smiley_bitmap, 32, 32);
    sh1107_update_display();
    sh1107_draw_text(15, 72, "Hack the planet!", true);
    sh1107_update_display();
    sleep_ms(5000);
    // Clear the display and buffer before exiting
    sh1107_clear_display();
    return 0;
}
