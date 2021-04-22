# bno055_verify_chip_id

The goal of this program is to read the CHIP_ID register of a BNO055 on an I2C
bus running at a baud rate 400 kHz and to verify that the CHIP_ID is 0xa0. The
program does this continuously and as fast as it can. The idea is to see how
many bits of data are transfered over the wire per second at 400 kHz.

Each time the CHIP_ID register is read, 39 bits of data are transfered and it
looks something like this:

```
S Addr Wr [A] Comm [A] S Addr Rd [A] [Data] NA P
```

It turns out that the CHIP_ID register can be read 1136 times per second. This
implies that 39 * 1136 = 44304 bits of data are transfered per second. This is
far less that the theoretical maximum of 400000 bits per second and is related
to the BNO055 stretching the I2C clock. With other devices like the BME280 a
lot more data can be transferred per second.

The program outputs one line per second and the output looks like this:

```
Continuously verify that the chip ID of a BNO055 is 0x0a
1: 1136 reads, 0 errors
2: 2272 reads, 0 errors
3: 3408 reads, 0 errors
4: 4544 reads, 0 errors
5: 5680 reads, 0 errors
6: 6816 reads, 0 errors
7: 7952 reads, 0 errors
8: 9088 reads, 0 errors
9: 10224 reads, 0 errors
10: 11360 reads, 0 errors
...
```

