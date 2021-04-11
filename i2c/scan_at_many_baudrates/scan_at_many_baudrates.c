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

static const uint MIN_BAUDRATE = 1000;
static const uint MAX_BAUDRATE = 2048000;

static const uint BAUDRATE_INC = 1000;

static const size_t MAX_TX_LEN = 10;

static const uint SCANS_PER_LINE = 32;

static bool device_at_addr(uint8_t addr) {
    for (uint i = 0; i < DEVICE_COUNT; ++i) {
        if (DEVICE_ADDRS[i] == addr) {
            return true;
        }
    }
    return false;
}

static uint write_to_all_addresses(
    i2c_inst_t *i2c, uint baudrate, const uint8_t *tx_buf, size_t tx_len
) {
    i2c_init(i2c, baudrate);

    // Return values of i2c_write_blocking calls are collected here.
    int rvals[MAX_I2C_ADDR + 1];

    // Avoid printf in this loop to ensure that i2c_write_blocking is called
    // as fast as possible.
    for (uint8_t addr = MIN_I2C_ADDR; addr <= MAX_I2C_ADDR; ++addr) {
        rvals[addr] = i2c_write_blocking(
            i2c_default, addr, tx_buf, tx_len, false
        );
    }

    uint error_count = 0;

    // Analyze results of i2c_write_blocking calls and print error error
    // messages if needed.
    for (uint8_t addr = MIN_I2C_ADDR; addr <= MAX_I2C_ADDR; ++addr) {
        bool dev_at_addr = device_at_addr(addr);
        if (dev_at_addr && rvals[addr] <= 0) {
            ++error_count;
            /*printf(
                "\n  addr 0x%02x, baudrate %d - error %d writing to device",
                 addr, baudrate, rvals[addr]
            );*/
        } else if (!dev_at_addr && (rvals[addr] >= 0)) {
            ++error_count;
            /*printf(
                "\n  addr 0x%02x, baudrate %d - unexpected device found",
                addr, baudrate
            );*/
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

    uint total_error_count = 0;
    uint total_scan_count = 0;

    uint8_t tx_buf[MAX_TX_LEN];
    for (size_t i = 0; i < MAX_TX_LEN; ++i) {
        tx_buf[i] = i;
    }

    while (true) {
        for (size_t tx_len = 1; tx_len <= MAX_TX_LEN; ++tx_len) {
            printf(
               "\n\n%d byte write to all addresses at increasing baudrates",
               tx_len
            );

            for (
                uint baudrate = MIN_BAUDRATE, line_error_count = 0;
                baudrate <= MAX_BAUDRATE;
                baudrate += BAUDRATE_INC, ++total_scan_count
            ) {
                if (total_scan_count % SCANS_PER_LINE == 0) {
                    printf(
                        "\nbaudrates %d to %d ",
                        baudrate,
                        baudrate + (BAUDRATE_INC * (SCANS_PER_LINE - 1))
                    );
                }

                uint error_count = write_to_all_addresses(
                    i2c_default, baudrate, tx_buf, tx_len
                );

                total_error_count += error_count;
                line_error_count += error_count;

                printf(".");

                if (total_scan_count % SCANS_PER_LINE == (SCANS_PER_LINE - 1)) {
                    printf(" %d errors", line_error_count);
                    line_error_count = 0;
                }
            }

            printf(
                "\n%d scans, %d errors",
                total_scan_count, total_error_count
            );
        }
    }
}

