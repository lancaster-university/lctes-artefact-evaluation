function set_gpio(state: number) {
    pins.digitalWritePin(DigitalPin.P1, state)
}

function high() {
    while (1) {
        set_gpio(1);
        control.spinScheduler();
    }
}

function low() {
    while (1) {
        set_gpio(0);
        control.spinScheduler();
    }
}

set_gpio(0);

control.inBackground(high)
control.inBackground(low)

control.releaseFiber();



