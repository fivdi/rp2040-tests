#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/resets.h"

static const int SUCCESS = 0;
static const int ERROR = -1;

static int print_i2c_bus_status() {
    bool sdaHigh = gpio_get(PICO_DEFAULT_I2C_SDA_PIN);
    bool sclHigh = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);

    printf(
        "\nSDA is %s, SCL is %s, the bus is %s.",
        sdaHigh ? "HIGH" : "LOW",
        sclHigh ? "HIGH" : "LOW",
        (!sdaHigh || !sclHigh) ? "blocked" : "not blocked"
    );

    return (sdaHigh && sclHigh) ? SUCCESS : ERROR;
}

static void block_bus_with_bme280() {
    const uint8_t BME280_ADDR = 0x76;
    const uint8_t ID_REG = 0xd0;

    if (i2c_write_blocking(i2c_default, BME280_ADDR, &ID_REG, 1, true) != 1) {
        printf("\nError: i2c_write_blocking failed.");
        return;
    }

    bool last_scl_state = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);
    if (!last_scl_state) {
        printf("\nError: expected scl to be low.");
        return;
    }

    // Read one byte
    i2c_default->hw->data_cmd =
        1 << I2C_IC_DATA_CMD_RESTART_LSB |
        1 << I2C_IC_DATA_CMD_STOP_LSB |
        1 << I2C_IC_DATA_CMD_CMD_LSB;

    uint bit_count = 0;

    while (!i2c_get_read_available(i2c_default)) {
        bool scl_state = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);
        if (scl_state != last_scl_state) {
            last_scl_state = scl_state;

            // When SCL goes high, the next bit is available on SDA.
            if (scl_state == 1) {
                // S Addr   R A Data     NA
                // x 11101101 0 01100000 1
                //              ^
                //              |
                //           Bit 11
                bit_count += 1;

                bool sda_state = gpio_get(PICO_DEFAULT_I2C_SDA_PIN);

                // As soon as a Data bit (bits 11 through 18) with value 0 is
                // received, reset the I2C peripheral. This results in the I2C
                // clock being stopped and SCL remains high. It also results
                // in SDA remaining low blocking the I2C bus.
                if (bit_count >= 11 && sda_state == 0) {
                    reset_block(RESETS_RESET_I2C0_BITS);
                    printf("\nBus should now be blocked.");
                    while (true) {
                        print_i2c_bus_status();
                        sleep_ms(1000);
                    }
                }
            }
        }
    }
}

int main() {
    stdio_init_all();

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    printf("\n---------------------------------------------------");
    if (print_i2c_bus_status() == ERROR) {
        printf("\nManually power Pico off and back on to unblock bus.");
    } else {
        printf("\nWill now attempt to block bus.");
        block_bus_with_bme280();
        printf("\nError: attempt to block bus failed.");
    }
}

