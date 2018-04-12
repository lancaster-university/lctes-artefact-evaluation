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