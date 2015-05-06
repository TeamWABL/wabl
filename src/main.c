/**
 * WABL main loop
 * @file    main.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-22 20:08:47
 * @edited  2015-05- 6 00:22:08
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
    //float uRef = 0.01;
	char print_buf[20];

    orient_init();
    uart_init();
    //encoder_init();

    sei();

    while(1){
        memset(print_buf, 0, 20);
        int16_t phi_dot = orient_get_phi_dot_raw();
        //x2_set_motor(MOTOR1, IMMEDIATE_DRIVE, 100);

        //double x = encoder_get_x(MOTOR1);
        
        //delay_ms(5);
        ////acquire states
        //x = encoder_get_x();
        //x_dot = trans_getXDot();
        //phi = orient_getPhi();
        //phi_dot = orient_getPhiDot();

        ////calculates new current reference
        //uRef = (phi * K[0]) + (phi_dot * K[1]) + (x * K[2]) + (x_dot * K[3]);

        //pass uRef (torque) to pid motor controller
		//float x = motor_update_pid(uRef,MOTOR1);
        //double test = 23.3234;
        //sprintf(print_buf, "%f\n", 20);
		sprintf(print_buf, "%d\n", phi_dot);	
		serial_send_blocking(XBEE, print_buf, sizeof(print_buf));
		//serial_send_blocking(XBEE, "testing\n", sizeof("testing\n"));
        delay_ms(50);
		//motor_update_pid_B(uRef);
        
    }
    return 0;
}
