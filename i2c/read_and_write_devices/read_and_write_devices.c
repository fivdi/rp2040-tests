#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static const uint MIN_BAUDRATE = 1000;
static const uint MAX_BAUDRATE = 2048000;

static const uint BAUDRATE_INC = 1000;

static const uint SCANS_PER_LINE = 32;

static const uint SUCCESS = 0;
static const uint ERROR = -1;

static uint read_word(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint16_t *word) {
    int rval = i2c_write_blocking(i2c, addr, &reg, 1, true);
    if (rval != 1) {
        return ERROR;
    }

    rval = i2c_read_blocking(i2c, addr, (uint8_t *) word, 2, false);
    if (rval != 2) {
        return ERROR;
    }

    return SUCCESS;
}

static uint write_word(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint16_t word) {
    uint8_t tx_data[] = {reg, (word >> 8) & 0xff, word & 0xff};

    int rval = i2c_write_blocking(i2c, addr, tx_data, 3, false);
    if (rval != 3) {
        return ERROR;
    }

    return SUCCESS;
}

static uint mcp9808(i2c_inst_t *i2c) {
    const uint8_t MCP9808_ADDR = 0x18;
    const uint8_t CRITICAL_TEMP_REG = 0x04;
    const uint8_t TEMP_REG = 0x05;

    uint error_count = 0;

    // Read the temperature a few times and make sure it looks reasonable.
    for (int i = 1; i <= 5; ++i) {
        uint16_t raw_temp;
        if (read_word(i2c, MCP9808_ADDR, TEMP_REG, &raw_temp) == ERROR) {
            ++error_count;
        } else {
            raw_temp = raw_temp << 8 | ((raw_temp >> 8) & 0xff);

            double celsius = (raw_temp & 0x0fff) / 16.0;
            if (raw_temp & 0x1000) {
                celsius -= 256;
            }

            // The WHO says ambient temperature is 15°C – 25°C or 30°C
            // depending on climatic conditions. Assume that a terperature
            // outside this range is an error.
            if (celsius < 15 || celsius > 30) {
                ++error_count;
            }
        }
    }

    // Write a few values to the critical temperature register and read them
    // back to ensure that they were written correctly.
    for (int i = 1; i <= 5; ++i) {
        uint16_t crit_temp_written = i << 6;

        uint rval = write_word(
            i2c, MCP9808_ADDR, CRITICAL_TEMP_REG, crit_temp_written
        );

        if (rval == ERROR) {
            ++error_count;
        } else {
            uint16_t crit_temp_read;

            rval = read_word(
                i2c, MCP9808_ADDR, CRITICAL_TEMP_REG, &crit_temp_read
            );

            if (rval == ERROR) {
                ++error_count;
            } else {
                crit_temp_read = crit_temp_read << 8 | ((crit_temp_read >> 8) & 0xff);

                if (crit_temp_read != crit_temp_written) {
                    ++error_count;
                }
            }
        }
    }

    return error_count;
}

int main() {
    sleep_ms(300); // Give the mcp9808 time to so it's first reading.

    stdio_init_all();

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    uint total_error_count = 0;
    uint total_scan_count = 0;

    while (true) {
        printf("\n\nread and write devices at increasing baudrates");

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

            i2c_init(i2c_default, baudrate);

            uint error_count = mcp9808(i2c_default);
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

