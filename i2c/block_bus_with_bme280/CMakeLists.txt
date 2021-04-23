cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(block_bus_with_bme280 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(block_bus_with_bme280
    block_bus_with_bme280.c
)

target_compile_definitions(block_bus_with_bme280 PRIVATE
  PARAM_ASSERTIONS_ENABLED_I2C=1
)

pico_enable_stdio_usb(block_bus_with_bme280 0)
pico_enable_stdio_uart(block_bus_with_bme280 1)

pico_add_extra_outputs(block_bus_with_bme280)

target_link_libraries(block_bus_with_bme280 pico_stdlib hardware_i2c)

