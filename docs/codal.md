# Testing codal

The tests we conducted are listed below.

## GPIO toggle time

This test is used to determine the time taken to toggle the GPIO. This time is then used as an offset in other other tests to remove this delay from our results.

### Steps to reproduce

1. Ensure `./codal/config.json` has `debug` and `heap_debug` set to 0.
1. Copy the contents of `tests/codal/gpio-base/BaseGPIOTest.cpp` to `codal/source/main.cpp`.
2. Compile the program by running `yt clean && yt build` in `./codal`.
3. From `./codal` copy `build/bbc-microbit-classic-gcc/source/microbit-samples-combined.hex` to the microbit.
4. Measure the positive width of the pulse using an oscilloscope, 1us per division.

### Test code

```cpp
#include "MicroBit.h"

MicroBit uBit;

void set_gpio(int pin_number, int state)
{
    switch(pin_number)
    {
        case 0:
            uBit.io.P0.setDigitalValue(state);
            break;
        case 1:
            uBit.io.P1.setDigitalValue(state);
            break;
        case 2:
            uBit.io.P2.setDigitalValue(state);
            break;
    }
}

int main()
{
    uBit.init();
    while(1)
    {
        set_gpio(1,1);
        set_gpio(1,0);
    }
}
```

### Where is this result used?

In each result where time is reported.

## Context switch time

This test determines the cost of our stack duplication approach with respect to time. We page between two fibers, and observe the impact this has on execution time using GPIO and an oscilloscope.

### Steps to reproduce

1. Ensure `./codal/config.json` has `debug` and `heap_debug` set to 0.
1. Copy the contents of `tests/codal/context-switch-time/ContextSwitchTest.cpp` to `codal/source/main.cpp`.
2. Compile the program by running `yt clean && yt build` in `./codal`.
3. From `./codal` copy `build/bbc-microbit-classic-gcc/source/microbit-samples-combined.hex` to the microbit.
4. Measure the positive width of the pulse using an oscilloscope, 1us per division.

**Do not forget to subtract the time taken to toggle a GPIO from these results.**

### Test code

```cpp
#include "MicroBit.h"

MicroBit uBit;

#define BUFFER_SIZE 0

void set_gpio(int pin_number, int state)
{
    switch(pin_number)
    {
        case 0:
            uBit.io.P0.setDigitalValue(state);
            break;
        case 1:
            uBit.io.P1.setDigitalValue(state);
            break;
        case 2:
            uBit.io.P2.setDigitalValue(state);
            break;
    }
}

void high()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif


    while(1)
    {
        set_gpio(1,1);
        schedule();
    }
}

void low()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif

    while(1)
    {
        set_gpio(1,0);
        schedule();
    }
}


int main()
{
    uBit.init();

    set_gpio(1,0);

    create_fiber(low);
    create_fiber(high);

    release_fiber();
}
```

### Where is this result used?

Figure 7, where we report context switch time vs. stack size, and Figure 6, where we report the context switch profiles for each device.

## Context switch longitudinal test

This test determines the cost of our stack duplication approach with respect to time. We force bytes onto the stack in two fibers, paging between them, and observe the impact this has on execution time using GPIO and an oscilloscope.

### Steps to reproduce

1. Ensure `./codal/config.json` has `debug` and `heap_debug` set to 0.
1. Copy the contents of `tests/codal/context-switch-time/ContextSwitchTest.cpp` to `codal/source/main.cpp`.
2. Compile the program by running `yt clean && yt build` in `./codal`.
3. From `./codal` copy `build/bbc-microbit-classic-gcc/source/microbit-samples-combined.hex` to the microbit.
4. Measure the positive width of the pulse using an oscilloscope.
5. Repeat steps 1 - 4 modifying the `BUFFER_SIZE` define at the top of the main program in increasing powers of 2.

**Do not forget to subtract the time taken to toggle a GPIO from these results.**

### Test code

```cpp
#include "MicroBit.h"

MicroBit uBit;

#define BUFFER_SIZE 0

void set_gpio(int pin_number, int state)
{
    switch(pin_number)
    {
        case 0:
            uBit.io.P0.setDigitalValue(state);
            break;
        case 1:
            uBit.io.P1.setDigitalValue(state);
            break;
        case 2:
            uBit.io.P2.setDigitalValue(state);
            break;
    }
}

void high()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif


    while(1)
    {
        set_gpio(1,1);
        schedule();
    }
}

void low()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif

    while(1)
    {
        set_gpio(1,0);
        schedule();
    }
}


int main()
{
    uBit.init();

    set_gpio(1,0);

    create_fiber(low);
    create_fiber(high);

    release_fiber();
}
```

### Where is this result used?

Figure 7, where we report context switch time vs. stack size.

## Tight loop execution time

This test counts from 0 to 100,000 using C++. After a full iteration, a GPIO is toggled, allowing us to calculate the time using an oscilloscope.

!!!note
    On the virtual machine, the result for this test will report ~114 ms due to the older version of `arm-none-eabi-gcc`. The results shown in the paper use version 7.2.1.

### Steps to reproduce

1. Ensure `./codal/config.json` has `debug` and `heap_debug` set to 0.
1. Copy the contents of `tests/codal/tight-loop/TightLoopTest.cpp` to `codal/source/main.cpp`.
2. Compile the program by running `yt clean && yt build` in `./codal`.
3. From `./codal` copy `build/bbc-microbit-classic-gcc/source/microbit-samples-combined.hex` to the microbit.
4. Measure the positive width of the pulse using an oscilloscope, 100ms per division should be adequate.

### Test code

```cpp

#include "MicroBit.h"

MicroBit uBit;

void set_gpio(int pin_number, int state)
{
    switch(pin_number)
    {
        case 0:
            uBit.io.P0.setDigitalValue(state);
            break;
        case 1:
            uBit.io.P1.setDigitalValue(state);
            break;
        case 2:
            uBit.io.P2.setDigitalValue(state);
            break;
    }
}

int main()
{
    uBit.init();

    set_gpio(1,0);

    while(1)
    {
        set_gpio(1,1);
        for(volatile int i = 0; i < 100000; i++)
        {
            i =i;
        }
        set_gpio(1,0);
        for(volatile int i = 0; i < 100000; i++)
        {
            i =i;
        }
    }

    release_fiber();
}
```

### Where is this result used?

Table 2, where we report the execution speed of each environment compared to MakeCode and Codal.

## Context switch stack usage

This test is used to determine the default stack depth in codal, and thus it's contribution to the time taken to page out the stack.

### Steps to reproduce

1. Set `debug` and `heap_debug` in `./codal/config.json` to 1.
1. Copy the contents of `tests/codal/context-switch-time/ContextSwitchTest.cpp` to `codal/source/main.cpp`.
2. Compile the program by running `yt clean && yt build` in `./codal`.
3. From `./codal` copy `build/bbc-microbit-classic-gcc/source/microbit-samples-combined.hex` to the microbit.
4. In minicom ([described here](index.md#test-procedure)) the output should read `sd: xxx bufferSize: xx`, the former shows the default stack depth in bytes for each fiber, the latter shows the amount of bytes allocated to contain the stack.

### Test code

```cpp
#include "MicroBit.h"

MicroBit uBit;

#define BUFFER_SIZE 0

void set_gpio(int pin_number, int state)
{
    switch(pin_number)
    {
        case 0:
            uBit.io.P0.setDigitalValue(state);
            break;
        case 1:
            uBit.io.P1.setDigitalValue(state);
            break;
        case 2:
            uBit.io.P2.setDigitalValue(state);
            break;
    }
}

void high()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif


    while(1)
    {
        set_gpio(1,1);
        schedule();
    }
}

void low()
{
#if BUFFER_SIZE > 0
    volatile char b[BUFFER_SIZE] = {0};
#endif

    while(1)
    {
        set_gpio(1,0);
        schedule();
    }
}


int main()
{
    uBit.init();

    set_gpio(1,0);

    create_fiber(low);
    create_fiber(high);

    release_fiber();
}
```

### Where is this result used?

Figure 6, where we show the context switch time per device, broken down by environment. We calculate each segment (Codal, Stack, MakeCode) using the time data gathered in the context switch time test. We then use codal as the benchmark to compute the impact of the stack for each; subtracting codal, and stack page times, gives us the overhead of MakeCode.

## Memory consumption

This results for this test are calculated when determining the consumption of MakeCode, please see "Memory consumption" in [makecode](makecode.md).