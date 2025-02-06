#include "pico/stdlib.h"
#include "sh1107_driver.h"

// Initialize SPI on the Pico
void spi_init_display() {
    spi_init(SPI_PORT, 1000 * 1000);  // 1 MHz
    gpio_set_function(18, GPIO_FUNC_SPI);
    gpio_set_function(19, GPIO_FUNC_SPI);

    // Configure CS, DC, RES as GPIO outputs
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    gpio_init(PIN_MISO);
    gpio_set_dir(PIN_MISO, GPIO_OUT);
    gpio_put(PIN_MISO, 1);

    gpio_init(PIN_RES);
    gpio_set_dir(PIN_RES, GPIO_OUT);
    gpio_put(PIN_RES, 1);
}

void sh1107_send_command(uint8_t command) {
    gpio_put(PIN_CS, 0);
    gpio_put(PIN_MISO, 0);  // Command mode
    spi_write_blocking(SPI_PORT, &command, 1);
    gpio_put(PIN_CS, 1);
}

void sh1107_send_data(uint8_t *data, size_t len) {
    gpio_put(PIN_CS, 0);
    gpio_put(PIN_MISO, 1);  // Data mode
    spi_write_blocking(SPI_PORT, data, len);
    gpio_put(PIN_CS, 1);
}

// Display buffer (128x128 / 8) = 2048 bytes (1 bit per pixel)
uint8_t display_buffer[2048] = {0};  // 128x128 / 8

void sh1107_update_display() {
    for (uint8_t page = 0; page < 16; page++) {  // Ensure all 16 pages update
        sh1107_send_command(SH110X_SETPAGEADDR | page);  // Set page address
        sh1107_send_command(0x00);  // Set lower column address
        sh1107_send_command(0x10);  // Set higher column address
        sh1107_send_data(&display_buffer[page * 128], 128);  // Ensure full row data
    }
}

void sh1107_clear_buffer() {
    memset(display_buffer, 0x00, sizeof(display_buffer));
}

void sh1107_clear_display() {
    sh1107_clear_buffer();
    sh1107_update_display();
}

void sh1107_test_fill() {
    for (uint16_t i = 0; i < sizeof(display_buffer); i++) {
        display_buffer[i] = i % 2 == 0 ? 0xFF : 0x00;
    }
    sh1107_update_display();
    sleep_ms(1000);
    sh1107_clear_display();
    sleep_ms(1000);
    sh1107_clear_buffer();

    for (uint16_t i = 0; i < sizeof(display_buffer); i++) {
        display_buffer[i] = i % 2 == 0 ? 0x55 : 0xAA;
    }

    sh1107_update_display();
    sleep_ms(1000);
    sh1107_clear_display();
    sleep_ms(1000);
    sh1107_clear_buffer();

    for (uint16_t i = 0; i < sizeof(display_buffer); i++) {
        display_buffer[i] = i % 2 == 0 ? 0x00 : 0xFF;
    }

    sh1107_update_display();
    sleep_ms(1000);
    sh1107_clear_display();
}

void sh1107_init() {

    sh1107_send_command(SH110X_DISPLAYOFF); // Display off
    sh1107_send_command(SH110X_SETDISPLAYCLOCKDIV); // Set display clock divide ratio/oscillator frequency
    sh1107_send_command(0x80); // Set clock divide ratio
    sh1107_send_command(SH110X_SETMULTIPLEX); // Set multiplex ratio
    sh1107_send_command(0x7F); // 1/128 duty (0x1F for 1/32)
    sh1107_send_command(SH110X_SETDISPLAYOFFSET); // Set display offset
    sh1107_send_command(0x00); // No offset
    sh1107_send_command(SH110X_SETSTARTLINE); // Set start line
    sh1107_send_command(SH110X_CHARGEPUMP); // Set charge pump
    sh1107_send_command(0x14); // Enable charge pump
    sh1107_send_command(SH110X_MEMORYMODE); // Set memory mode
    sh1107_send_command(0x00); // Horizontal addressing mode
    sh1107_send_command(SH110X_SEGREMAP | 0x00);  // Flip horizontal (Segment Re-map)
    sh1107_send_command(SH110X_COMSCANINC);       // Ensure text starts at top
    //sh1107_send_command(SH110X_COMSCANDEC);      // Fix row order (inverts text)
    sh1107_send_command(0xDC); // Set display start line
    sh1107_send_command(0x00);
    sh1107_send_command(0x00); // Set lower column address
    sh1107_send_command(0x10 | (32 >> 4)); // Set upper column address (Start at col 32)
    sh1107_send_command(SH110X_SETCOMPINS); // Set COM pins hardware configuration
    sh1107_send_command(0x12); // Alternative COM pin configuration
    sh1107_send_command(SH110X_SETCONTRAST); // Set contrast control
    sh1107_send_command(0xCF); // Set contrast to 0xCF
    sh1107_send_command(SH110X_SETPRECHARGE); // Set pre-charge period
    sh1107_send_command(0xF1); // Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK
    sh1107_send_command(SH110X_SETVCOMDETECT); // Set VCOMH Deselect Level
    sh1107_send_command(0x40); // Set VCOMH Deselect Level to 0.77*Vcc
    sh1107_send_command(SH110X_DISPLAYALLON_RESUME); // Set entire display on
    sh1107_send_command(SH110X_NORMALDISPLAY); // Set normal display
    sh1107_send_command(SH110X_DISPLAYON); // Display on

    sh1107_clear_display();
}
