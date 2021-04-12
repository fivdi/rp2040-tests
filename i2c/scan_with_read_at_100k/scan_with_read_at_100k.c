#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// TODO
// List of addresses of all I2C devices on the I2C bus.
// Change if needed.
static const uint8_t DEVICE_ADDRS[] = {
    0x18, // mcp9808
    0x29, // tsc34725
    0x76  // bme280
};
static const uint DEVICE_COUNT = sizeof(DEVICE_ADDRS) / sizeof(uint8_t);

static const uint8_t MIN_I2C_ADDR = 0x08;
static const uint8_t MAX_I2C_ADDR = 0x77;

static bool device_at_addr(uint8_t addr) {
    for (uint i = 0; i < DEVICE_COUNT; ++i) {
        if (DEVICE_ADDRS[i] == addr) {
            return true;
        }
    }
    return false;
}

static uint scan_with_read_at_100k(i2c_inst_t *i2c) {
    uint error_count = 0;

    i2c_init(i2c, 100 * 1000);

    for (uint8_t addr = MIN_I2C_ADDR; addr <= MAX_I2C_ADDR; ++addr) {
        bool dev_at_addr = device_at_addr(addr);

        uint8_t rx_byte;
        int rval = i2c_read_blocking(i2c_default, addr, &rx_byte, 1, false);

        if ((dev_at_addr && rval != 1) || (!dev_at_addr && rval >= 0)) {
            ++error_count;
        }
    }

    return error_count;
}

int main() {
    stdio_init_all();

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    for (uint scan_count = 1, error_count = 0; ; ++scan_count) {
        error_count += scan_with_read_at_100k(i2c_default);

        if (scan_count % 100 == 0) {
            printf("\n%d scans, %d errors", scan_count, error_count);
        }
    }
}

