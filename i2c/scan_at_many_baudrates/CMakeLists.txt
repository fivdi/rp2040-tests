cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(scan_at_many_baudrates C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(scan_at_many_baudrates
    scan_at_many_baudrates.c
)

target_compile_definitions(scan_at_many_baudrates PRIVATE
  PARAM_ASSERTIONS_ENABLED_I2C=1
)

pico_enable_stdio_usb(scan_at_many_baudrates 0)
pico_enable_stdio_uart(scan_at_many_baudrates 1)

pico_add_extra_outputs(scan_at_many_baudrates)

target_link_libraries(scan_at_many_baudrates pico_stdlib hardware_i2c)

