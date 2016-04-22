/**
 *
 * @file    computer_interface.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:16
 * @edited  2016-04-22 16:49:33
 */

#ifndef COMPUTER_INTERFACE_H
#define COMPUTER_INTERFACE_H

#include <pololu/orangutan.h>

#define XBEE    UART0

/**
 * @brief   Sets up baud rate for UART communication
 */
void computer_interface_init(void);

void computer_interface_check_for_new_bytes(void);

void process_new_bytes(uint8_t byte);

void command_handler(uint8_t opcode);

#endif //UART_H
