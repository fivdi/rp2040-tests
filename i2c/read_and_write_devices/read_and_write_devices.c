#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static const uint MIN_BAUDRATE = 2000;
static const uint MAX_BAUDRATE = 2000000;

static const uint BAUDRATE_INC = 1000;

static const uint SCANS_PER_LINE = 32;

static const int SUCCESS = 0;
static const int ERROR = -1;

static int read_byte(
    i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *byte
) {
    int rval = i2c_write_blocking(i2c, addr, &reg, 1, true);
    if (rval != 1) {
        return ERROR;
    }

    rval = i2c_read_blocking(i2c, addr, (uint8_t *) byte, 1, false);
    if (rval != 1) {
        return ERROR;
    }

    return SUCCESS;
}

static int read_word(
    i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint16_t *word
) {
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

static int write_word(
    i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint16_t word
) {
    uint8_t tx_data[] = {reg, (word >> 8) & 0xff, word & 0xff};

    int rval = i2c_write_blocking(i2c, addr, tx_data, 3, false);
    if (rval != 3) {
        return ERROR;
    }

    return SUCCESS;
}

static uint access_mcp9808(i2c_inst_t *i2c) {
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

        int rval = write_word(
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
                crit_temp_read =
                    crit_temp_read << 8 | ((crit_temp_read >> 8) & 0xff);

                if (crit_temp_read != crit_temp_written) {
                    ++error_count;
                }
            }
        }
    }

    return error_count;
}

static uint access_bme280(i2c_inst_t *i2c) {
    const uint8_t BME280_ADDR = 0x76;
    const uint8_t ID_REG = 0xd0;

    uint error_count = 0;

    // Read the ID a few times and make sure it's correct
    for (int i = 1; i <= 5; ++i) {
        uint8_t id;

        if (read_byte(i2c, BME280_ADDR, ID_REG, &id) == ERROR) {
            ++error_count;
        } else if (id != 0x60) {
            ++error_count;
        }
    }

    return error_count;
}

static uint access_tsc34725(i2c_inst_t *i2c) {
    const uint8_t TSC34725_ADDR = 0x29;
    const uint8_t ID_REG = 0x92;

    uint error_count = 0;

    // Read the ID a few times and make sure it's correct
    for (int i = 1; i <= 5; ++i) {
        uint8_t id;

        if (read_byte(i2c, TSC34725_ADDR, ID_REG, &id) == ERROR) {
            ++error_count;
        } else if (id != 0x44) {
            ++error_count;
        }
    }

    return error_count;
}

int main() {
    sleep_ms(300); // Give the mcp9808 time to do it's first reading.

    stdio_init_all();

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    uint total_error_count = 0;
    uint total_scan_count = 0;

    uint max_baudrate = MIN_BAUDRATE +
        ((MAX_BAUDRATE - MIN_BAUDRATE) / BAUDRATE_INC) * BAUDRATE_INC;

    while (true) {
        printf("\n\nread and write devices at increasing baudrates");

        uint line_error_count = 0;
        uint line_scan_count = 0;

        // Scan bus at all baudrates from MIN_BAUDRATE to max_baudrate in
        // in increments of BAUDRATE_INC.
        for (
            uint baudrate = MIN_BAUDRATE;
            baudrate <= max_baudrate;
            baudrate += BAUDRATE_INC
        ) {
            // Print baudrates at the start of a line.
            if (line_scan_count % SCANS_PER_LINE == 0) {
                uint max_baudrate_line = MIN(
                    baudrate + (BAUDRATE_INC * (SCANS_PER_LINE - 1)),
                    max_baudrate
                );

                printf("\nbaudrates %d to %d ", baudrate, max_baudrate_line);
            }

            i2c_init(i2c_default, baudrate);

            uint error_count = access_mcp9808(i2c_default);
            error_count += access_bme280(i2c_default);
            error_count += access_tsc34725(i2c_default);
            printf(".");

            line_error_count += error_count;
            line_scan_count += 1;

            total_error_count += error_count;
            total_scan_count += 1;

            // Print error information at the end of a line
            if (line_scan_count == SCANS_PER_LINE ||
                baudrate == max_baudrate
            ) {
                printf(
                    " %d of %d errors", line_error_count, total_error_count
                );

                line_error_count = 0;
                line_scan_count = 0;
            }
        }

        printf(
            "\n%d scans, %d errors",
            total_scan_count, total_error_count
        );
    }
}

