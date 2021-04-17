cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(bus_scan_issue_278 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(bus_scan_issue_278
    bus_scan_issue_278.c
)

target_compile_definitions(bus_scan_issue_278 PRIVATE
  PARAM_ASSERTIONS_ENABLED_I2C=1
)

pico_enable_stdio_usb(bus_scan_issue_278 0)
pico_enable_stdio_uart(bus_scan_issue_278 1)

pico_add_extra_outputs(bus_scan_issue_278)

target_link_libraries(bus_scan_issue_278 pico_stdlib hardware_i2c)

