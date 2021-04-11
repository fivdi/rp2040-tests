# scan_at_many_baudrates

A test case for
[this pico-sdk issue](https://github.com/raspberrypi/pico-sdk/issues/278).

The goal of this program is to see if it can detect anything unexpected when
scanning the I2C bus with `i2c_write_blocking`. Ideally, there should be no
errors.

The program performs tests at I2C baudrates of 1000 to 2048000 in steps of
1000 baud.

Assuming there is a MCP9808 (0x18), TSC34725 (0x29) and BME280 (0x76) on the
I2C bus, this program should output the information shown below when the issue
is fixed.

**Important**: If other devices are on the I2C bus, the array `DEVICE_ADDRS`
at the top of `send_at_many_baudrates.c` will need to be changed accordingly.

```
1 byte write to all addresses at increasing baudrates
baudrates 1000 to 32000 ................................ 0 errors
baudrates 33000 to 64000 ................................ 0 errors
baudrates 65000 to 96000 ................................ 0 errors
baudrates 97000 to 128000 ................................ 0 errors
baudrates 129000 to 160000 ................................ 0 errors
baudrates 161000 to 192000 ................................ 0 errors
baudrates 193000 to 224000 ................................ 0 errors
baudrates 225000 to 256000 ................................ 0 errors
baudrates 257000 to 288000 ................................ 0 errors
baudrates 289000 to 320000 ................................ 0 errors
baudrates 321000 to 352000 ................................ 0 errors
baudrates 353000 to 384000 ................................ 0 errors
baudrates 385000 to 416000 ................................ 0 errors
baudrates 417000 to 448000 ................................ 0 errors
baudrates 449000 to 480000 ................................ 0 errors
baudrates 481000 to 512000 ................................ 0 errors
baudrates 513000 to 544000 ................................ 0 errors
baudrates 545000 to 576000 ................................ 0 errors
baudrates 577000 to 608000 ................................ 0 errors
baudrates 609000 to 640000 ................................ 0 errors
baudrates 641000 to 672000 ................................ 0 errors
baudrates 673000 to 704000 ................................ 0 errors
baudrates 705000 to 736000 ................................ 0 errors
baudrates 737000 to 768000 ................................ 0 errors
baudrates 769000 to 800000 ................................ 0 errors
baudrates 801000 to 832000 ................................ 0 errors
baudrates 833000 to 864000 ................................ 0 errors
baudrates 865000 to 896000 ................................ 0 errors
baudrates 897000 to 928000 ................................ 0 errors
baudrates 929000 to 960000 ................................ 0 errors
baudrates 961000 to 992000 ................................ 0 errors
baudrates 993000 to 1024000 ................................ 0 errors
baudrates 1025000 to 1056000 ................................ 0 errors
baudrates 1057000 to 1088000 ................................ 0 errors
baudrates 1089000 to 1120000 ................................ 0 errors
baudrates 1121000 to 1152000 ................................ 0 errors
baudrates 1153000 to 1184000 ................................ 0 errors
baudrates 1185000 to 1216000 ................................ 0 errors
baudrates 1217000 to 1248000 ................................ 0 errors
baudrates 1249000 to 1280000 ................................ 0 errors
baudrates 1281000 to 1312000 ................................ 0 errors
baudrates 1313000 to 1344000 ................................ 0 errors
baudrates 1345000 to 1376000 ................................ 0 errors
baudrates 1377000 to 1408000 ................................ 0 errors
baudrates 1409000 to 1440000 ................................ 0 errors
baudrates 1441000 to 1472000 ................................ 0 errors
baudrates 1473000 to 1504000 ................................ 0 errors
baudrates 1505000 to 1536000 ................................ 0 errors
baudrates 1537000 to 1568000 ................................ 0 errors
baudrates 1569000 to 1600000 ................................ 0 errors
baudrates 1601000 to 1632000 ................................ 0 errors
baudrates 1633000 to 1664000 ................................ 0 errors
baudrates 1665000 to 1696000 ................................ 0 errors
baudrates 1697000 to 1728000 ................................ 0 errors
baudrates 1729000 to 1760000 ................................ 0 errors
baudrates 1761000 to 1792000 ................................ 0 errors
baudrates 1793000 to 1824000 ................................ 0 errors
baudrates 1825000 to 1856000 ................................ 0 errors
baudrates 1857000 to 1888000 ................................ 0 errors
baudrates 1889000 to 1920000 ................................ 0 errors
baudrates 1921000 to 1952000 ................................ 0 errors
baudrates 1953000 to 1984000 ................................ 0 errors
baudrates 1985000 to 2016000 ................................ 0 errors
baudrates 2017000 to 2048000 ................................ 0 errors
2048 scans, 0 errors

2 byte write to all addresses at increasing baudrates
baudrates 1000 to 32000 ................................ 0 errors
baudrates 33000 to 64000 ................................ 0 errors
baudrates 65000 to 96000 ................................ 0 errors
baudrates 97000 to 128000 ................................ 0 errors
baudrates 129000 to 160000 ................................ 0 errors
baudrates 161000 to 192000 ................................ 0 errors
baudrates 193000 to 224000 ................................ 0 errors
baudrates 225000 to 256000 ................................ 0 errors
baudrates 257000 to 288000 ................................ 0 errors
baudrates 289000 to 320000 ................................ 0 errors
baudrates 321000 to 352000 ................................ 0 errors
baudrates 353000 to 384000 ................................ 0 errors
baudrates 385000 to 416000 ................................ 0 errors
baudrates 417000 to 448000 ................................ 0 errors
baudrates 449000 to 480000 ................................ 0 errors
baudrates 481000 to 512000 ................................ 0 errors
baudrates 513000 to 544000 ................................ 0 errors
baudrates 545000 to 576000 ................................ 0 errors
baudrates 577000 to 608000 ................................ 0 errors
baudrates 609000 to 640000 ................................ 0 errors
baudrates 641000 to 672000 ................................ 0 errors
baudrates 673000 to 704000 ................................ 0 errors
baudrates 705000 to 736000 ................................ 0 errors
baudrates 737000 to 768000 ................................ 0 errors
baudrates 769000 to 800000 ................................ 0 errors
baudrates 801000 to 832000 ................................ 0 errors
baudrates 833000 to 864000 ................................ 0 errors
baudrates 865000 to 896000 ................................ 0 errors
baudrates 897000 to 928000 ................................ 0 errors
baudrates 929000 to 960000 ................................ 0 errors
baudrates 961000 to 992000 ................................ 0 errors
baudrates 993000 to 1024000 ................................ 0 errors
baudrates 1025000 to 1056000 ................................ 0 errors
baudrates 1057000 to 1088000 ................................ 0 errors
baudrates 1089000 to 1120000 ................................ 0 errors
baudrates 1121000 to 1152000 ................................ 0 errors
baudrates 1153000 to 1184000 ................................ 0 errors
baudrates 1185000 to 1216000 ................................ 0 errors
baudrates 1217000 to 1248000 ................................ 0 errors
baudrates 1249000 to 1280000 ................................ 0 errors
baudrates 1281000 to 1312000 ................................ 0 errors
baudrates 1313000 to 1344000 ................................ 0 errors
baudrates 1345000 to 1376000 ................................ 0 errors
baudrates 1377000 to 1408000 ................................ 0 errors
baudrates 1409000 to 1440000 ................................ 0 errors
baudrates 1441000 to 1472000 ................................ 0 errors
baudrates 1473000 to 1504000 ................................ 0 errors
baudrates 1505000 to 1536000 ................................ 0 errors
baudrates 1537000 to 1568000 ................................ 0 errors
baudrates 1569000 to 1600000 ................................ 0 errors
baudrates 1601000 to 1632000 ................................ 0 errors
baudrates 1633000 to 1664000 ................................ 0 errors
baudrates 1665000 to 1696000 ................................ 0 errors
baudrates 1697000 to 1728000 ................................ 0 errors
baudrates 1729000 to 1760000 ................................ 0 errors
baudrates 1761000 to 1792000 ................................ 0 errors
baudrates 1793000 to 1824000 ................................ 0 errors
baudrates 1825000 to 1856000 ................................ 0 errors
baudrates 1857000 to 1888000 ................................ 0 errors
baudrates 1889000 to 1920000 ................................ 0 errors
baudrates 1921000 to 1952000 ................................ 0 errors
baudrates 1953000 to 1984000 ................................ 0 errors
baudrates 1985000 to 2016000 ................................ 0 errors
baudrates 2017000 to 2048000 ................................ 0 errors
4096 scans, 0 errors

3 byte write to all addresses at increasing baudrates
baudrates 1000 to 32000 ................................ 0 errors
baudrates 33000 to 64000 ................................ 0 errors
baudrates 65000 to 96000 ................................ 0 errors
...
```

