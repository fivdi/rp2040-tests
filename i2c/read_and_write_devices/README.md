# read_and_write_devices

A test case for
[this pico-sdk issue](https://github.com/raspberrypi/pico-sdk/issues/278).

The goal of this program is to see if it can detect any errors when
continuously writing to and reading from devices on the I2C bus.
Ideally, there should be no errors.

The program performs tests at I2C baudrates of 2000 to 2000000 in steps of
1000 baud.

This program requires an MCP9808, BME280 and TCS34725 on the I2C bus to
function correctly.

Assuming the required devices are on the I2C bus, this program should output
the following when the issue is fixed:

```
read and write devices at increasing baudrates
baudrates 2000 to 33000 ................................ 0 of 0 errors
baudrates 34000 to 65000 ................................ 0 of 0 errors
baudrates 66000 to 97000 ................................ 0 of 0 errors
baudrates 98000 to 129000 ................................ 0 of 0 errors
baudrates 130000 to 161000 ................................ 0 of 0 errors
baudrates 162000 to 193000 ................................ 0 of 0 errors
baudrates 194000 to 225000 ................................ 0 of 0 errors
baudrates 226000 to 257000 ................................ 0 of 0 errors
baudrates 258000 to 289000 ................................ 0 of 0 errors
baudrates 290000 to 321000 ................................ 0 of 0 errors
baudrates 322000 to 353000 ................................ 0 of 0 errors
baudrates 354000 to 385000 ................................ 0 of 0 errors
baudrates 386000 to 417000 ................................ 0 of 0 errors
baudrates 418000 to 449000 ................................ 0 of 0 errors
baudrates 450000 to 481000 ................................ 0 of 0 errors
baudrates 482000 to 513000 ................................ 0 of 0 errors
baudrates 514000 to 545000 ................................ 0 of 0 errors
baudrates 546000 to 577000 ................................ 0 of 0 errors
baudrates 578000 to 609000 ................................ 0 of 0 errors
baudrates 610000 to 641000 ................................ 0 of 0 errors
baudrates 642000 to 673000 ................................ 0 of 0 errors
baudrates 674000 to 705000 ................................ 0 of 0 errors
baudrates 706000 to 737000 ................................ 0 of 0 errors
baudrates 738000 to 769000 ................................ 0 of 0 errors
baudrates 770000 to 801000 ................................ 0 of 0 errors
baudrates 802000 to 833000 ................................ 0 of 0 errors
baudrates 834000 to 865000 ................................ 0 of 0 errors
baudrates 866000 to 897000 ................................ 0 of 0 errors
baudrates 898000 to 929000 ................................ 0 of 0 errors
baudrates 930000 to 961000 ................................ 0 of 0 errors
baudrates 962000 to 993000 ................................ 0 of 0 errors
baudrates 994000 to 1025000 ................................ 0 of 0 errors
baudrates 1026000 to 1057000 ................................ 0 of 0 errors
baudrates 1058000 to 1089000 ................................ 0 of 0 errors
baudrates 1090000 to 1121000 ................................ 0 of 0 errors
baudrates 1122000 to 1153000 ................................ 0 of 0 errors
baudrates 1154000 to 1185000 ................................ 0 of 0 errors
baudrates 1186000 to 1217000 ................................ 0 of 0 errors
baudrates 1218000 to 1249000 ................................ 0 of 0 errors
baudrates 1250000 to 1281000 ................................ 0 of 0 errors
baudrates 1282000 to 1313000 ................................ 0 of 0 errors
baudrates 1314000 to 1345000 ................................ 0 of 0 errors
baudrates 1346000 to 1377000 ................................ 0 of 0 errors
baudrates 1378000 to 1409000 ................................ 0 of 0 errors
baudrates 1410000 to 1441000 ................................ 0 of 0 errors
baudrates 1442000 to 1473000 ................................ 0 of 0 errors
baudrates 1474000 to 1505000 ................................ 0 of 0 errors
baudrates 1506000 to 1537000 ................................ 0 of 0 errors
baudrates 1538000 to 1569000 ................................ 0 of 0 errors
baudrates 1570000 to 1601000 ................................ 0 of 0 errors
baudrates 1602000 to 1633000 ................................ 0 of 0 errors
baudrates 1634000 to 1665000 ................................ 0 of 0 errors
baudrates 1666000 to 1697000 ................................ 0 of 0 errors
baudrates 1698000 to 1729000 ................................ 0 of 0 errors
baudrates 1730000 to 1761000 ................................ 0 of 0 errors
baudrates 1762000 to 1793000 ................................ 0 of 0 errors
baudrates 1794000 to 1825000 ................................ 0 of 0 errors
baudrates 1826000 to 1857000 ................................ 0 of 0 errors
baudrates 1858000 to 1889000 ................................ 0 of 0 errors
baudrates 1890000 to 1921000 ................................ 0 of 0 errors
baudrates 1922000 to 1953000 ................................ 0 of 0 errors
baudrates 1954000 to 1985000 ................................ 0 of 0 errors
baudrates 1986000 to 2000000 ............... 0 of 0 errors
1999 scans, 0 errors

read and write devices at increasing baudrates
baudrates 2000 to 33000 ................................ 0 of 0 errors
baudrates 34000 to 65000 ................................ 0 of 0 errors
baudrates 66000 to 97000 ................................ 0 of 0 errors
baudrates 98000 to 129000 ................................ 0 of 0 errors
baudrates 130000 to 161000 ................................ 0 of 0 errors
baudrates 162000 to 193000 ................................ 0 of 0 errors
baudrates 194000 to 225000 ................................ 0 of 0 errors
baudrates 226000 to 257000 ................................ 0 of 0 errors
baudrates 258000 to 289000 ................................ 0 of 0 errors
baudrates 290000 to 321000 ................................ 0 of 0 errors
baudrates 322000 to 353000 ................................ 0 of 0 errors
baudrates 354000 to 385000 ................................ 0 of 0 errors
baudrates 386000 to 417000 ................................ 0 of 0 errors
baudrates 418000 to 449000 ................................ 0 of 0 errors
baudrates 450000 to 481000 ................................ 0 of 0 errors
baudrates 482000 to 513000 ................................ 0 of 0 errors
baudrates 514000 to 545000 ................................ 0 of 0 errors
baudrates 546000 to 577000 ................................ 0 of 0 errors
baudrates 578000 to 609000 ................................ 0 of 0 errors
baudrates 610000 to 641000 ................................ 0 of 0 errors
baudrates 642000 to 673000 ................................ 0 of 0 errors
baudrates 674000 to 705000 ................................ 0 of 0 errors
baudrates 706000 to 737000 ................................ 0 of 0 errors
baudrates 738000 to 769000 ................................ 0 of 0 errors
baudrates 770000 to 801000 ................................ 0 of 0 errors
baudrates 802000 to 833000 ................................ 0 of 0 errors
baudrates 834000 to 865000 ................................ 0 of 0 errors
baudrates 866000 to 897000 ................................ 0 of 0 errors
baudrates 898000 to 929000 ................................ 0 of 0 errors
baudrates 930000 to 961000 ................................ 0 of 0 errors
baudrates 962000 to 993000 ................................ 0 of 0 errors
baudrates 994000 to 1025000 ................................ 0 of 0 errors
baudrates 1026000 to 1057000 ................................ 0 of 0 errors
baudrates 1058000 to 1089000 ................................ 0 of 0 errors
baudrates 1090000 to 1121000 ................................ 0 of 0 errors
baudrates 1122000 to 1153000 ................................ 0 of 0 errors
baudrates 1154000 to 1185000 ................................ 0 of 0 errors
baudrates 1186000 to 1217000 ................................ 0 of 0 errors
baudrates 1218000 to 1249000 ................................ 0 of 0 errors
baudrates 1250000 to 1281000 ................................ 0 of 0 errors
baudrates 1282000 to 1313000 ................................ 0 of 0 errors
baudrates 1314000 to 1345000 ................................ 0 of 0 errors
baudrates 1346000 to 1377000 ................................ 0 of 0 errors
baudrates 1378000 to 1409000 ................................ 0 of 0 errors
baudrates 1410000 to 1441000 ................................ 0 of 0 errors
baudrates 1442000 to 1473000 ................................ 0 of 0 errors
baudrates 1474000 to 1505000 ................................ 0 of 0 errors
baudrates 1506000 to 1537000 ................................ 0 of 0 errors
baudrates 1538000 to 1569000 ................................ 0 of 0 errors
baudrates 1570000 to 1601000 ................................ 0 of 0 errors
baudrates 1602000 to 1633000 ................................ 0 of 0 errors
baudrates 1634000 to 1665000 ................................ 0 of 0 errors
baudrates 1666000 to 1697000 ................................ 0 of 0 errors
baudrates 1698000 to 1729000 ................................ 0 of 0 errors
baudrates 1730000 to 1761000 ................................ 0 of 0 errors
baudrates 1762000 to 1793000 ................................ 0 of 0 errors
baudrates 1794000 to 1825000 ................................ 0 of 0 errors
baudrates 1826000 to 1857000 ................................ 0 of 0 errors
baudrates 1858000 to 1889000 ................................ 0 of 0 errors
baudrates 1890000 to 1921000 ................................ 0 of 0 errors
baudrates 1922000 to 1953000 ................................ 0 of 0 errors
baudrates 1954000 to 1985000 ................................ 0 of 0 errors
baudrates 1986000 to 2000000 ............... 0 of 0 errors
3998 scans, 0 errors

read and write devices at increasing baudrates
baudrates 2000 to 33000 ................................ 0 of 0 errors
baudrates 34000 to 65000 ................................ 0 of 0 errors
baudrates 66000 to 97000 ................................ 0 of 0 errors
...
```

