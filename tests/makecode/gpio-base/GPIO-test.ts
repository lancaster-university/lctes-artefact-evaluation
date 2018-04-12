function set_gpio(state: number) {
    pins.digitalWritePin(DigitalPin.P1, state)
}

while (true) {
    set_gpio(1);
    set_gpio(0);
}
