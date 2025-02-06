# SH1107 OLED Driver for Raspberry Pi Pico

## Overview
This project implements a driver for the SH1107-based 128x128 OLED display (Pimoroni PIM473) using SPI communication with the Raspberry Pi Pico. The driver supports:

- Text rendering
- Basic shapes (lines, rectangles, circles)
- Bitmap image display

## Features
- 📟 **128x128 monochrome OLED display support**
- 🔠 **Custom font rendering**
- 📏 **Basic graphics primitives (lines, rectangles, circles)**
- 🖼️ **Bitmap rendering**
- 🔌 **Optimized SPI communication**

---

## Bill of Materials (BOM)

| Quantity | Component                  | Description                             | Supplier |
|----------|----------------------------|-----------------------------------------|----------|
| 1        | Raspberry Pi Pico           | RP2040-based microcontroller board     | [Raspberry Pi](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html) |
| 1        | Pimoroni PIM473 OLED Display | 1.3" SH1107 128x128 OLED (SPI)         | [Pimoroni](https://shop.pimoroni.com/products/1-12-oled-breakout) |
| 6        | Jumper Wires (Male-Male)    | For connecting Pico to OLED            | Any      |
| 1        | USB Cable (Micro USB)       | For powering/programming the Pico      | Any      |

---

## Pinout Connections (SPI)

### Raspberry Pi Pico ↔ Pimoroni PIM473 (SH1107 OLED)

| Pico Pin | Function | OLED Pin (PIM473) |
|----------|----------|-------------------|
| **GP16** | MISO     | N/C (Unused)      |
| **GP17** | CS       | CS                |
| **GP18** | SCK      | SCK               |
| **GP19** | MOSI     | MOSI              |
| **GND**  | GND      | GND               |
| **3V3**  | 3.3V     | VCC               |

*Note:* The display uses **SPI0** on the Raspberry Pi Pico.
RST is not required.
---

## Installation & Usage
### Prerequisites
- Raspberry Pi Pico SDK installed
- CMake & GNU Arm Toolchain setup
- Pimoroni PIM473 OLED connected to the Raspberry Pi Pico

### Build & Flash
```sh
mkdir build && cd build
cmake ..
make -j4
picotool load -f firmware.uf2
```

## Author
@retromanc3r

## Acknowledgements
Special thanks to Adafruit for their [SH110x](https://github.com/adafruit/Adafruit_SH110x) and [GFX](https://github.com/adafruit/Adafruit-GFX-Library) libraries which were helpful in designing this driver and getting the Pimoroni PIM473 1.2 inch OLED SPI breakout working with the Raspberry Pi Pico!
