/**
 * 
 * @file    uart.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:13
 * @edited  2015-04-28 10:02:15
 */

#include <pololu/orangutan.h>
#include "uart.h"

void uart_init(int port, unsigned long baudRate){
    serial_set_baud_rate(port, baudRate);
}
