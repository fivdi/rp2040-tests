# block_bus_with_grove_lcd

This program demonstrates how a Grove 16 x 2 LCD will block the I2C bus by
holding SDA low if an attempt is made to read a byte from the displays I2C
controller.

If this program is run when the I2C bus is not blocked it will output the
following:

```
-------------------------------------------------------
SDA and SCL should be HIGH, if not, the bus is blocked.
SDA is HIGH.
SCL is HIGH.
The bus is not blocked.
Will now read one byte from LCD to block bus
SDA is LOW, SCL is HIGH, the bus is blocked.
SDA is LOW, SCL is HIGH, the bus is blocked.
SDA is LOW, SCL is HIGH, the bus is blocked.
...
```

If this program is run when the I2C bus is blocked it will output the
following:

```
-------------------------------------------------------
SDA and SCL should be HIGH, if not, the bus is blocked.
SDA is LOW.
SCL is HIGH.
The bus is blocked.
Manually power Pico off and back on to unblock.
```

