/*
 * 
 * @file    computer_interface.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:13
 * @edited  2016-04-22 17:10:12
 */

#include <pololu/orangutan.h>
#include <stdio.h>
#include <stdint.h>
#include "computer_interface.h"

char read_buff[36]; //ring buffer for characters read in
uint8_t read_buff_head = 0; //head index position of ring buffer


void computer_interface_init(void){
    serial_set_baud_rate(XBEE, 19200UL);
    serial_receive_ring(XBEE, read_buff, sizeof(read_buff));
}

void computer_interface_check_for_new_bytes(void){

    while (serial_get_received_bytes(XBEE) != read_buff_head){
        //process new bytes
        process_new_bytes(read_buff[read_buff_head]);

        read_buff_head = (read_buff_head + 1) % sizeof(read_buff);
    }
    //static uint8_t previous_byte3 = 0;
    //static uint8_t previous_byte2 = 0;
    //static uint8_t previous_byte = 0;

    ////read in next byte
    ////char read_buff[1];
    ////serial_receive(XBEE, read_buff, 1);
    //uint8_t current_byte = read_buff[0];
    //serial_send_blocking(XBEE, read_buff, sizeof(read_buff));

    ////check for sequence signalling command from computer
    ////if (previous_byte3 == 0x45){
    ////    if (previous_byte2 == 0xC2){
    ////        if (previous_byte == 0x21){
    ////            computer_interface_command_handler(current_byte);
    ////        }
    ////    }
    ////}

    ////move bytes to previous bytes
    //previous_byte3 = previous_byte2;
    //previous_byte2 = previous_byte;
    //previous_byte = current_byte;
}

void process_new_bytes(uint8_t byte){
    static uint8_t previous_byte3 = 0;
    static uint8_t previous_byte2 = 0;
    static uint8_t previous_byte = 0;

    //check for sequence signalling command from computer
    //if (previous_byte3 == 0x45){
    //    if (previous_byte2 == 0xC2){
    //        if (previous_byte == 0x21){
    if (previous_byte3 == 'A'){
        if (previous_byte2 == 'B'){
            if (previous_byte == 'C'){
                command_handler(byte);
            }
        }
    }

    //move bytes to previous bytes
    previous_byte3 = previous_byte2;
    previous_byte2 = previous_byte;
    previous_byte = byte;
}

void command_handler(uint8_t opcode){
    //handle commands
    if (opcode == 'A'){
        //get id (return "WABL")
        char id[] = "WABL";
        serial_send_blocking(XBEE, id, sizeof(id));

    }else if (opcode == 0x02){
        //set motor kp
    }else if (opcode == 0x03){
        //set motor ki
    }else if (opcode == 0x04){
        //set lqr x
    }else if (opcode == 0x05){
        //set lqr x dot
    }else if (opcode == 0x06){
        //set lqr phi
    }else if (opcode == 0x07){
        //set lqr phi dot
    }
}

//void computer_interface_command_handler(uint8_t opcode){
//    if (opcode == 0x01){
//        //get id (return "WABL")
//        char *id = "WABL";
//        serial_send(XBEE, id, sizeof(id));
//
//    }else if (opcode == 0x02){
//        //set motor kp
//    }else if (opcode == 0x03){
//        //set motor ki
//    }else if (opcode == 0x04){
//        //set lqr x
//    }else if (opcode == 0x05){
//        //set lqr x dot
//    }else if (opcode == 0x06){
//        //set lqr phi
//    }else if (opcode == 0x07){
//        //set lqr phi dot
//    }
//}
