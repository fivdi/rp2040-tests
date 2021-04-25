# block_bus_with_bme280

This program demonstrates how a BME280 will block the I2C bus by holding SDA
low if the I2C clock is stopped at the appropriate point in time during an I2C
read.

To function correctly this program need the modifications from
[this PR](https://github.com/raspberrypi/pico-sdk/pull/331).

If this program is run when the I2C bus is not blocked it will output the
following:

```
---------------------------------------------------
SDA is HIGH, SCL is HIGH, the bus is not blocked.
Will now attempt to block bus.
Bus should now be blocked.
SDA is LOW, SCL is HIGH, the bus is blocked.
SDA is LOW, SCL is HIGH, the bus is blocked.
SDA is LOW, SCL is HIGH, the bus is blocked.
...
```

If this program is run when the I2C bus is blocked it will output the
following:

```
---------------------------------------------------
SDA is LOW, SCL is HIGH, the bus is blocked.
Manually power Pico off and back on to unblock bus.
```

