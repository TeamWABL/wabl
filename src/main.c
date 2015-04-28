/**
 * WABL main loop
 * @file    main.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-22 20:08:47
 * @edited  2015-04-28 16:03:37
 */

#define F_CPU   20000000
#include <avr/io.h>
#include <util/delay.h>
#include <pololu/orangutan.h>
#include <stdint.h>
#include <stdio.h>

#include "io_defs.h"
#include "modules.h"

//testing
#include "test_code/test.h"
//testing

int main(void){
    //setup
    //led_hb_init();
    //float x;
    //float x_dot;
    //float phi;
    //float phi_dot;
    
    float uRef = 0.2;
	char print_buf[80];

    //float K[4] = {-10.4113, -2.5702, -0.8970, -1.5861};
    //i2c_init();

    serial_set_baud_rate(USB_COMM, 19200UL);
    serial_set_baud_rate(XBEE, 19200UL);
    while(1){
        //serial_send_blocking(USB_COMM, "test\r\n", 6);
        //test_i2c();
        delay_ms(50);
        //led_hb();

        ////acquire states
        //x = trans_getX();
        //x_dot = trans_getXDot();
        //phi = orient_getPhi();
        //phi_dot = orient_getPhiDot();

        ////calculates new current reference
        //uRef = (phi * K[0]) + (phi_dot * K[1]) + (x * K[2]) + (x_dot * K[3]);

        //pass uRef (torque) to pid motor controller
        //double test = 23.3234;
        //sprintf(print_buf, "%d\n", 20);
		sprintf(print_buf, "%f \n", motor_update_pid_A(1.0));	
		serial_send_blocking(XBEE, print_buf, 80);
		//motor_update_pid_B(uRef);
        
    }
    return 0;
}
