#include <atmel_start.h>
#include "driver_examples.h"
#include "pins.h"

void delays(void) { // delay some
    for (volatile int i=1299999; i>0; i--) {
        // empty loop
    }
}

void blink_two(void) {
    // clear first
    PORT->Group[PORTA].OUTCLR.reg  = (uint32_t)(1 << 23); // PA23 //  0 13 pinwrite  // D13
    for (int blinks=2; blinks >0; blinks--) {
        PORT->Group[PORTA].OUTTGL.reg  = (uint32_t)(1 << 23); // PA23 //    13 pintoggle // D13
        delays();
    }
}

void blink_awhile(void) {
    for (int iter=22; iter >0; iter--) {
        blink_two();
    }
}

int main(void)
{
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    SystemInit();
    pins_setup(); // initialize GPIO D13 PA23

    blink_awhile(); // is the clock running?

    USART_5_example();
    /* Replace with your application code */

    while (1) {
    }
}
