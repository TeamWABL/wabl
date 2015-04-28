/**
 *
 * @file    uart.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:16
 * @edited  2015-04-28 09:48:38
 */

#ifndef UART_H
#define UART_H

#include <pololu/orangutan.h>

#define XBEE    UART0

void uart_init(void);

#endif //UART_H
