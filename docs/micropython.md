# Testing micropython

The tests we conducted are listed below.

## Tight loop execution time (byte code compiled)

This test is used to determine the overhead of a bytecode interpretter on the microbit. The test runs a tight spin loop using a python program toggling a gpio every 100,000 increments of a count.

*A precompiled hex file (`./test/micropython/tight-loop/compiled/microbit-micropython-bytecode-compiled.hex`) is provided for convenience.*

### Steps to reproduce

1. Navigate to the [micropython online editor](https://python.microbit.org/v/1)
1. Copy the contents of `./tests/tight-loop/compiled/tight-loop-compiled-test.py` into the editor.
1. Click download and drag the outputted hex file onto the microbit device.
4. Set oscilloscope to 10s per division.
5. Measure the width of the high pulse.

### Where is this result used?

Table 2, where we report the execution speed of each environment compared to MakeCode and Codal.


## Tight loop execution time (fully interpretted)

This test is used to determine the overhead of a full interpretter on the microbit. The test runs a tight spin loop using a python program toggling a gpio every 100,000 increments of a count.

### Steps to reproduce

1. Flash `./micropython/microbit-micropython.hex` (the full interpretter) onto the microbit.
2. Connect minicom ([described here](index.md#test-procedure))to the microbit at 115200 baud.
3. Press `ctrl + e` in minicom to enter paste mode (`>>>` should change to `===`)
4. Copy and paste `./tests/tight-loop/interpeted/tight-loop-test.py` into minicom.
5. Press `ctrl + d` to begin execution
4. Set oscilloscope to 50s per division.
5. Measure the width of the high pulse.

### Test code

```py
while True:
    pin1.write_digital(0)

    for i in range(0,100000):
        i = i

    pin1.write_digital(1)

    for i in range(0,100000):
        i = i
```

### Where is this result used?

This result is not used, but will appear in Table 2, where we report the execution speed of each environment compared to MakeCode and Codal for Camera Ready.