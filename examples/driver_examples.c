/* Code generated from Atmel Start - overwritten; do make a copy. */

/* driver_examples.c */

/* wa1tnr - August, 2018 LGPL v2.1 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/* Terminal Input Buffer for interpreter */
const uint8_t maxtib = 16;

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
void USART_0_example(void) {
    char tib[maxtib];
    // struct io_descriptor *io;
    // usart_sync_get_io_descriptor(&USART_0, &io);
    usart_sync_get_desc();
    // usart_sync_enable(&USART_0);
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
        io_write(io, (uint8_t *)tib, 1); // 1  is also length
    }
}
