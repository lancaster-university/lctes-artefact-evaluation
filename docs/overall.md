# MakeCode and Codal: Intuitive and Efficient Embedded Systems Programming for Education

In these markdown files, you will find the information required to reproduce our results gathered for the paper using the micro:bit.

## Physical requirements

- Must have a micro:bit
- Must have a copy of our debian virtual machine with testing environment.
- Must have an oscilloscope available.

## Required ability
- Must be competent with debian, and terminal.
- Must have some experience with an oscilloscope, or is willing to learn how to use one!
- Understand how to use a serial terminal.

## Test procedure

The root directory is arranged in the following form:

- `codal` contains the codal build environment which you will use to conduct codal tests.
- `docs` contains the documentation for tests and this overview document.
- `espruino` contains the espruino interpretter used when testing espruino.
- `makecode` contains a modified copy of the executable web editor that can be run locally.
- `tests` contains all of the tests, grouped by each environment, their use is described in the `docs` folder. e.g. `docs/codal.md` describes all tests that are contained in `tests/codal/*`.

Tests either use a serial terminal to validate output, or use an oscilloscope to measure waveforms, in either case the setup pictured below should be adequate for both tests:

![oscilloscope image](images/oscilloscope.JPG)

The micro:bit is connected to a PC over USB (top of the micro:bit), which also exposes a serial port for a PC to connect to for serial output from the micro:bit. The scope has one probe lead connected to channel one, this probe lead connects to the micro:bit's ground pin (far right of the micro:bit), and samples pin P1 (yellow cable connected to the micro:bit). All tests use pin P1, so no reconfiguration of this setup will be required.

For information on how to use an oscilloscope we recommend this [sparkfun tutorial](https://learn.sparkfun.com/tutorials/how-to-use-an-oscilloscope/anatomy-of-an-o-scope#horizontal).

## Reproducibility

There are various factors which could affect the accuracy of the results we report in the paper:

- Toolchains used to build programs
- Oscilloscope quality
- Calibration of the Oscilloscope

In reproducing these results ourselves we have noted small variations of +/- 30 microseconds, as we have updated our own toolchains.

## What is a micro:bit?

The [micro:bit](https://microbit.org) is a small embedded computer designed for computer science education, MakeCode and Codal were initially designed for the micro:bit, evolving and supporting other devices over time.

## Why only the micro:bit?

As testing a large number of devices is complex, especially in a distributed artifact evaluation format, it was agreed that we would provide the micro:bit which is representative of the results in the paper.