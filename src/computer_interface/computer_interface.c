/*
 * 
 * @file    computer_interface.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 09:17:13
 * @edited  2016-05- 4 01:50:20
 */

#include <pololu/orangutan.h>
#include <stdio.h>
#include <stdint.h>
#include "computer_interface.h"
#include "../motor/motor.h"
#include "../lqr/lqr.h"
#include "../modules.h"

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
    static uint8_t previous_byte7 = 0;
    static uint8_t previous_byte6 = 0;
    static uint8_t previous_byte5 = 0;
    static uint8_t previous_byte4 = 0;
    static uint8_t previous_byte3 = 0;
    static uint8_t previous_byte2 = 0;
    static uint8_t previous_byte = 0;

    //check for sequence signalling command from computer
    //if (previous_byte3 == 0x45){
    //    if (previous_byte2 == 0xC2){
    //        if (previous_byte == 0x21){
    //if (previous_byte7 == 'a'){
    //    if (previous_byte6 == 'b'){
    //        if (previous_byte5 == 'c'){
    //            if (previous_byte4 == 'd'){
    if (previous_byte7 == 0x45){
        if (previous_byte6 == 0xC2){
            if (previous_byte5 == 0x21){
                if (previous_byte4 == 0x01){
                    //get_id (return "WABL")
                    char id[] = "WABL";
                    serial_send_blocking(XBEE, id, sizeof(id));
                }else{
                    double data = ((uint32_t) previous_byte3 << 24 | (uint32_t) previous_byte2 << 16 | previous_byte << 8 | byte);
                    if (previous_byte4 == 0x02){
                        //set_motor_kp
                        motor_set_kp(data);
                    }else if (previous_byte4 == 0x03){
                        //set_motor_ki
                        motor_set_ki(data);
                    }else if (previous_byte4 == 0x04){
                        //set_lqr_x
                        lqr_set_k_x(data);
                    }else if (previous_byte4 == 0x05){
                        //set_lqr_x_dot
                        lqr_set_k_x_dot(data);
                    }else if (previous_byte4 == 0x06){
                        //set_lqr_phi
                        lqr_set_k_phi(data);
                    }else if (previous_byte4 == 0x07){
                        //set_lqr_phi_dot
                        lqr_set_k_phi_dot(data);
                    }
                }
            }
        }
    }

    //move bytes to previous bytes
    previous_byte7 = previous_byte6;
    previous_byte6 = previous_byte5;
    previous_byte5 = previous_byte4;
    previous_byte4 = previous_byte3;
    previous_byte3 = previous_byte2;
    previous_byte2 = previous_byte;
    previous_byte = byte;
}
