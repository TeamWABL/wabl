/*
 * 
 * @file    uart.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:13
 * @edited  2015-05-19 21:06:05
 */

#include <pololu/orangutan.h>
#include "uart.h"

void uart_init(void){
    serial_set_baud_rate(XBEE, 19200UL);
}
