# Testing Espruino

The tests we conducted are listed below.

## Tight loop execution time

This test is used to determine the overhead of a full interpretter on the microbit. The test runs a tight spin loop using a python program toggling a gpio every 100,000 increments of a count.

### Steps to reproduce

1. Flash `espruino_1v95_microbit.hex` to the microbit.
2. Connect minicom ([described here](index.md#test-procedure)) to the microbit at 9600 baud.
3. Copy and paste `./tests/espruino/tight-loop/tight-loop.js` into minicom.
4. Set oscilloscope to 25s per division.
5. Measure the result.

### Test code

```js
while(true){digitalWrite(D1,false); for(var i = 0; i < 100000; i++){i=i;} digitalWrite(D1,true); for(var i = 0; i < 100000; i++){i=i;} }
```

### Where is this result used?

Table 2, where we report the execution speed of each environment compared to MakeCode and Codal.


