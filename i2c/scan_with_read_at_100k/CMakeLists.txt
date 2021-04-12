cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(scan_with_read_at_100k C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(scan_with_read_at_100k
    scan_with_read_at_100k.c
)

pico_enable_stdio_usb(scan_with_read_at_100k 0)
pico_enable_stdio_uart(scan_with_read_at_100k 1)

pico_add_extra_outputs(scan_with_read_at_100k)

target_link_libraries(scan_with_read_at_100k pico_stdlib hardware_i2c)

