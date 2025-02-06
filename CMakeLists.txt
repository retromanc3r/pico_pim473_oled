cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(../../pico-sdk/pico_sdk_init.cmake)

project(pico_pim473_oled)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(pico_pim473_oled
    src/pico_pim_oled.c
    src/driver/sh1107_driver.c
    src/fonts/sh1107_font.c
    src/gfx/sh1107_bitmap.c
    src/gfx/sh1107_draw.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(pico_pim473_oled pico_stdlib hardware_spi)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(pico_pim473_oled)
