function set_gpio(state: number) {
    pins.digitalWritePin(DigitalPin.P1, state)
}

while (true) {
    set_gpio(0);
    for (let i = 0; i < 100000; i++) {
        i = i;
    }
    set_gpio(1);
    for (let i = 0; i < 100000; i++) {
        i = i;
    }
}