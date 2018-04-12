# Testing Espruino

The tests we conducted are listed below.

## Tight loop execution time

This test is used to determine the overhead of a full interpretter on the microbit. The test runs a tight spin loop using a python program toggling a gpio every 100,000 increments of a count.

### Steps to reproduce

1. Flash `espruino_1v95_microbit.hex` to the microbit.
2. Connect a serial terminal to the microbit at 9600 baud.
3. Copy and paste `./tests/espruino/tight-loop/tight-loop.js` into your connected serial terminal.
4. Set oscilloscope to 25s per division.
5. Measure the result.

### Where is this result used?

Table 2, where we report the execution speed of each environment compared to MakeCode and Codal.


