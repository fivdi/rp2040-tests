cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(read_and_write_devices C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(read_and_write_devices
    read_and_write_devices.c
)

pico_enable_stdio_usb(read_and_write_devices 0)
pico_enable_stdio_uart(read_and_write_devices 1)

pico_add_extra_outputs(read_and_write_devices)

target_link_libraries(read_and_write_devices pico_stdlib hardware_i2c)

