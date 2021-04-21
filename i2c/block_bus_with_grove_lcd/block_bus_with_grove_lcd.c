#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/resets.h"

const uint8_t GROVE_LCD_ADDR = 0x3e;

static void block_bus_with_grove_lcd() {
    i2c_default->hw->enable = 0;
    i2c_default->hw->tar = GROVE_LCD_ADDR;
    i2c_default->hw->enable = 1;

    // Read 1 byte from LCD.
    i2c_default->hw->data_cmd =
        1 << I2C_IC_DATA_CMD_RESTART_LSB |
        1 << I2C_IC_DATA_CMD_STOP_LSB |
        1 << I2C_IC_DATA_CMD_CMD_LSB; // -> 1 for read

    while (!i2c_get_read_available(i2c_default)) {
        sleep_ms(1000);

        bool sdaHigh = gpio_get(PICO_DEFAULT_I2C_SDA_PIN);
        bool sclHigh = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);

        printf(
            "\nSDA is %s, SCL is %s, the bus is %s.",
            sdaHigh ? "HIGH" : "LOW",
            sclHigh ? "HIGH" : "LOW",
            (!sdaHigh || !sclHigh) ? "blocked" : "not blocked"
        );
    }
}

int main() {
    stdio_init_all();

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    bool sdaHigh = gpio_get(PICO_DEFAULT_I2C_SDA_PIN);
    bool sclHigh = gpio_get(PICO_DEFAULT_I2C_SCL_PIN);

    printf("\n-------------------------------------------------------");
    printf("\nSDA and SCL should be HIGH, if not, the bus is blocked.");
    printf("\nSDA is %s.", sdaHigh ? "HIGH" : "LOW");
    printf("\nSCL is %s.", sclHigh ? "HIGH" : "LOW");

    if (!sdaHigh || !sclHigh) {
        printf("\nThe bus is blocked.");
        printf("\nManually power Pico off and back on to unblock.");
    } else {
        printf("\nThe bus is not blocked.");
        printf("\nWill now read one byte from LCD to block bus.");
        block_bus_with_grove_lcd();
    }
}

