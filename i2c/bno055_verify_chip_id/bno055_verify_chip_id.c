#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static const int SUCCESS = 0;
static const int ERROR = -1;

static int read_byte(
    i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *byte
) {
    if (i2c_write_blocking(i2c, addr, &reg, 1, true) != 1 ||
        i2c_read_blocking(i2c, addr, (uint8_t *) byte, 1, false) != 1) {
        return ERROR;
    }

    return SUCCESS;
}

static int bno055_verify_chip_id(i2c_inst_t *i2c) {
    const uint8_t BNO055_ADDR = 0x28;
    const uint8_t ID_REG = 0x00;

    uint8_t id;

    if (read_byte(i2c, BNO055_ADDR, ID_REG, &id) == ERROR || id != 0xa0) {
        return ERROR;
    }

    return SUCCESS;
}

int main() {
    stdio_init_all();

    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    i2c_init(i2c_default, 400 * 1000);

    printf("\nContinuously verify that the chip ID of a BNO055 is 0x0a");

    uint error_count = 0;

    for (int i = 1; ; ++i) {
        if (bno055_verify_chip_id(i2c_default) != SUCCESS) {
           error_count += 1;
        }

        // At 400000 baud, the chip ID can be verified 1136 time per second.
        if (i % 1136 == 0) {
           printf("\n%d: %d reads, %d errors", i / 1136, i, error_count);
        }
    }
}

