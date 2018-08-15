/* Code generated from Atmel Start - overwritten; do make a copy. */

/* driver_examples.c */

/* wa1tnr - August, 2018 LGPL v2.1 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/* Terminal Input Buffer for interpreter */
#define maxtib 16

struct io_descriptor *io;

void usart_sync_get_desc(void) {
    usart_sync_get_io_descriptor(&USART_0, &io);
}

void usart_sync_enbl(void) {
    usart_sync_enable(&USART_0);
}

void fg_yellow(void) { // foreground yellow
    io_write(io, (uint8_t *)"            ", 12);
    io_write(io, (uint8_t *)"\033\133", 2); // ESC [
    io_write(io, (uint8_t *)"\063\063", 2); // 33 - yellow fg
    io_write(io, (uint8_t *)"m", 1);        // for the stanza
}

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */

char tib[maxtib];
uint8_t *buf;

void filter(void) {

    /* stanza -- control H */
    if ((uint8_t) *buf == 8) { // Control H
        io_write(io, (uint8_t *) "\010",  1);
        io_write(io, (uint8_t *) " ",  1);
        return;
    }

    /* stanza -- rubout */
    if ((uint8_t) *buf == 127) { // Control H
        io_write(io, (uint8_t *) "\010",  1);
        io_write(io, (uint8_t *) " ",  1);
        io_write(io, (uint8_t *) "\010",  1); // rubout needs to travel to the left here
        return;
    }

    /* stanza -- CR */
    if ((uint8_t) *buf == 13) { // CR or 0x0d
        io_write(io, (uint8_t *) " ok",  3);
        io_write(io, (uint8_t *) "\015",  1); // 0x0d
        io_write(io, (uint8_t *) "\012",  1); // 0x0a // your terminal may want differently
        return;
    }
}

void USART_0_example(void) {
    usart_sync_get_desc();
    usart_sync_enbl();

    io_write(io, (uint8_t *)
        "Program is configured for 38400 bps speed.\r\n\r\n",        46);
    io_write(io, (uint8_t *)
        "Target MCU board is Adafruit Feather M4 Express.\r\n\r\n",  52);
    io_write(io, (uint8_t *)
        "UART pins TX and RX used with CP2104 bridge.\r\n\r\n",      48);

    /*
        12345678901234567890123456789012345678901234567890
                10        20        30        40        50
    */

    io_write(io, (uint8_t *)  "Hello World!\r\n",  14);
    io_write(io, (uint8_t *)"  type something: ",  18);

    fg_yellow(); // color it!

    while(-1) { // endless loop, read one char, write one char (echo)
        io_read(io,  (uint8_t *)tib, 1); // 1  is length
        buf = (uint8_t *)tib;
        filter();
        io_write(io, (uint8_t *)tib, 1); // 1  is also length
    }
}
