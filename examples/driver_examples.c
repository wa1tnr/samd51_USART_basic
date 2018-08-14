/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/* Terminal Input Buffer for interpreter */
const uint8_t maxtib = 16;

/**
 * Example of using USART_0 to write "Hello World" using the IO abstraction.
 */
void USART_0_example(void)
{
	char tib[maxtib];
	struct io_descriptor *io;
	usart_sync_get_io_descriptor(&USART_0, &io);
	usart_sync_enable(&USART_0);

	io_write(io, (uint8_t *)  "Hello World!\r\n",  14);
	io_write(io, (uint8_t *)"  type something: ",  18);

	while(-1) { // endless loop, read one char, write one char (echo)
		io_read(io,  (uint8_t *)tib, 1); // 1  is length
		io_write(io, (uint8_t *)tib, 1); // 1  is also length
        }
}
