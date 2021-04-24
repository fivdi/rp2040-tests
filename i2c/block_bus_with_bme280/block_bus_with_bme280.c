#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/resets.h"

static const int BUS_NOT_BLOCKED = 0;
static const int BUS_BLOCKED = -1;

static int get_and_print_bus_status() {
    bool sda_high = gpio_get(PICO_DEFAULT_I2C_SDA_PIN);
    bool scl_high = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);

    printf(
        "\nSDA is %s, SCL is %s, the bus is %s.",
        sda_high ? "HIGH" : "LOW",
        scl_high ? "HIGH" : "LOW",
        (sda_high && scl_high) ? "not blocked" : "blocked"
    );

    return (sda_high && scl_high) ? BUS_NOT_BLOCKED : BUS_BLOCKED;
}

static void block_bus_with_bme280() {
    const uint8_t BME280_ADDR = 0x76;
    const uint8_t ID_REG = 0xd0;

    if (i2c_write_blocking(i2c_default, BME280_ADDR, &ID_REG, 1, true) != 1) {
        printf("\nError: i2c_write_blocking failed.");
        return;
    }

    // After the above write the I2C peripheral should hold the bus. Wait
    // until this is the case.
    bool last_scl_state = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);
    while (last_scl_state) {
        last_scl_state = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);
    }

    // Read one byte. The bits transfered should look like this:
    //
    //   S Addr   R A Data     NA
    //   x 11101101 0 01100000 1
    //   ^            ^      ^
    //   |            |      |
    // Bit1         Bit11  Bit18
    i2c_default->hw->data_cmd =
        1 << I2C_IC_DATA_CMD_RESTART_LSB |
        1 << I2C_IC_DATA_CMD_STOP_LSB |
        1 << I2C_IC_DATA_CMD_CMD_LSB;

    uint bit_count = 0;

    while (!i2c_get_read_available(i2c_default) && bit_count < 18) {
        bool scl_state = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);

        if (scl_state != last_scl_state) {
            last_scl_state = scl_state;

            // When SCL goes high, the next bit is available on SDA.
            if (scl_state == 1) {
                bool bit = gpio_get(PICO_DEFAULT_I2C_SDA_PIN);

                bit_count += 1;

                // As soon as a Data bit (bits 11 through 18) with value 0 is
                // received, reset the I2C peripheral. This results in the I2C
                // clock being stopped and SCL remains high. It also results
                // in SDA remaining low blocking the I2C bus.
                if (bit_count >= 11 && bit == 0) {
                    reset_block(RESETS_RESET_I2C0_BITS);
                    printf("\nBus should now be blocked.");
                    while (true) {
                        get_and_print_bus_status();
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
    if (get_and_print_bus_status() == BUS_BLOCKED) {
        printf("\nManually power Pico off and back on to unblock bus.");
    } else {
        printf("\nWill now attempt to block bus.");
        block_bus_with_bme280();
        printf("\nError: attempt to block bus failed.");
    }
}

