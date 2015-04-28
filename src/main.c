/**
 * WABL main loop
 * @file    main.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-22 20:08:47
 * @edited  2015-04-28 09:00:10
 */

#define F_CPU   20000000
#include <avr/io.h>
#include <util/delay.h>
#include <pololu/orangutan.h>
#include <stdint.h>
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
    //
    float uRef = 0;

    //float K[4] = {-10.4113, -2.5702, -0.8970, -1.5861};
    i2c_init();
    while(1){
        test_i2c();
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
        //motor_update_pid_A(uRef);
		//motor_update_pid_B(uRef);
        
    }
    return 0;
}
