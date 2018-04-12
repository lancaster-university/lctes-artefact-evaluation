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
