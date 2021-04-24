# scan_with_read_at_100k

The goal of this program is to see if it can detect anything unexpected when
continuously scanning the I2C bus with `i2c_read_blocking` using a baudrate of
100k. Ideally, there should be no errors.

Assuming there is a MCP9808 (0x18), TCS34725 (0x29) and BME280 (0x76) on the
I2C bus, this program should output the information shown below.

**Important**: If other devices are on the I2C bus, the array `DEVICE_ADDRS`
at the top of `scan_with_read_at_100k.c` will need to be changed accordingly.

```
100 scans, 0 errors
200 scans, 0 errors
300 scans, 0 errors
400 scans, 0 errors
500 scans, 0 errors
600 scans, 0 errors
700 scans, 0 errors
800 scans, 0 errors
900 scans, 0 errors
1000 scans, 0 errors
...
```

