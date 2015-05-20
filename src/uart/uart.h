/**
 *
 * @file    uart.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:16
 * @edited  2015-05-19 21:06:30
 */

#ifndef UART_H
#define UART_H

#include <pololu/orangutan.h>

#define XBEE    UART0

/**
 * @brief   Sets up baud rate for UART communication
 */
void uart_init(void);

#endif //UART_H
