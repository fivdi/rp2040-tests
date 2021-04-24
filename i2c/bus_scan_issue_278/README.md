# bus_scan_issue_278

A test case for
[this pico-sdk issue](https://github.com/raspberrypi/pico-sdk/issues/278).

The goal of this program is to scan the I2C bus using `i2c_write_blocking`
rather that `i2c_read_blocking`.

Assuming there is a MCP9808 (0x18), TCS34725 (0x29) and BME280 (0x76) on the
I2C bus, this program should output the following when the issue is fixed:

```
i2c_write_blocking test
   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
00 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
10 .  .  .  .  .  .  .  .  @  .  .  .  .  .  .  .
20 .  .  .  .  .  .  .  .  .  @  .  .  .  .  .  .
30 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
40 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
50 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
60 .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
70 .  .  .  .  .  .  @  .  .  .  .  .  .  .  .  .
```

