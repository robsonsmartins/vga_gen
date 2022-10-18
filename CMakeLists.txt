# ---------------------------------------------------------------------------
# USB EPROM/Flash Programmer
#
# Copyright (2022) Robson Martins
#
# This work is licensed under a Creative Commons Attribution-NonCommercial-
# ShareAlike 4.0 International License.
# ---------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16)

include(pico_sdk_import.cmake)
project(vga C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(vga 
      hal/gpio.cpp
      hal/multicore.cpp
      circuits/74hc595.cpp
      main.cpp
)

target_include_directories(vga PUBLIC .)

target_compile_options(vga PRIVATE -DPICO_STDIO_USB_ENABLE_RESET_VIA_VENDOR_INTERFACE=0)
target_compile_options(vga PRIVATE -DPICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS=0)

target_link_libraries(vga 
        pico_stdlib
        pico_multicore
)

pico_enable_stdio_usb(vga 1)
pico_enable_stdio_uart(vga 0)
pico_add_extra_outputs(vga)
