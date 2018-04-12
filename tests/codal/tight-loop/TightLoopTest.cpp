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
