/**
 * WABL main loop
 * @file    main.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-22 20:08:47
 * @edited  2015-05-10 21:51:09
 */

#define F_CPU   20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <pololu/orangutan.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "io_defs.h"
#include "modules.h"

//testing
#include "test_code/test.h"
//testing

int main(void){
    //uart setup

    uart_init();
	char print_buf[120];

    serial_send_blocking(XBEE, "Initializing UART...", 20);
    serial_send_blocking(XBEE, "done.\n", 6);

    // timer setup
    serial_send_blocking(XBEE, "Initializing Timer...", 21);

    sysT_init();

    sysTimer16_t print_timer;
    sysT_16_init(&print_timer);

    serial_send_blocking(XBEE, "done.\n", 6);


    //state acquisition setup
    serial_send_blocking(XBEE, "Initializing state acquisition...", 33);
    double phi;
    double phi_dot;
    
    double a_x;
    double a_x_dot;
    double b_x;
    double b_x_dot;

    orient_init();
    encoder_init();

    serial_send_blocking(XBEE, "done.\n", 6);

    sei();


    while(1){
        if (!safety_battery_critical()){
            //clear print buf
            memset(print_buf, 0, 120);

            //acquire state variables
            phi = orient_get_phi();
            phi_dot = orient_get_phi_dot();
            
            a_x = encoder_get_x(MOTOR1);
            a_x_dot = encoder_get_x_dot(MOTOR1);

            b_x = encoder_get_x(MOTOR2);
            b_x_dot = encoder_get_x_dot(MOTOR2);
            
            //delay_ms(5);
            ////acquire states
            //x = encoder_get_x();
            //x_dot = trans_getXDot();
            //phi = orient_getPhi();
            //phi_dot = orient_getPhiDot();

            ////calculates new current reference
            //uRef = (phi * K[0]) + (phi_dot * K[1]) + (x * K[2]) + (x_dot * K[3]);

            //pass uRef (torque) to pid motor controller
            //motor_update_pid(uRef,MOTOR1);
            //double test = 23.3234;
            //sprintf(print_buf, "%f\n", 20);
            //sprintf(print_buf, "%f mm\t%f mm/s\n", x, v);
            //sprintf(print_buf, "phi = %10f, phi_raw = %10f, phi_dot = %10f, phi_dot_raw = %10f\n", phi, phi_raw, phi_dot, phi_dot_raw);	
            //sprintf(print_buf, "%f\n", phi_dot_raw);	
            serial_send_blocking(XBEE, print_buf, sizeof(print_buf));
            //serial_send_blocking(XBEE, "testing\n", sizeof("testing\n"));
            delay_ms(25);
            //motor_update_pid_B(uRef);
        }else{
            //play game over
            sound_play_melody(BATTERY_CRITICAL);
            while(is_playing());
            cli();
            break;
        }
    }
    return 0;
}

//1ms timer interrupt
ISR(TIMER1_COMPA_vect){
    static uint8_t orient_update_tmr;
    if (++orient_update_tmr == 10){
        orient_update_tmr = 0;
        orient_update(5);
        encoder_update(5);
    }

    //sysT_timer_service();
}
