cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(bno055_verify_chip_id C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(bno055_verify_chip_id
    bno055_verify_chip_id.c
)

target_compile_definitions(bno055_verify_chip_id PRIVATE
  PARAM_ASSERTIONS_ENABLED_I2C=1
)

pico_enable_stdio_usb(bno055_verify_chip_id 0)
pico_enable_stdio_uart(bno055_verify_chip_id 1)

pico_add_extra_outputs(bno055_verify_chip_id)

target_link_libraries(bno055_verify_chip_id pico_stdlib hardware_i2c)

