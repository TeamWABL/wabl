/**
 * 
 * @file    main.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-22 20:08:47
 * @edited  2015-03-26 03:51:24
 */

#define F_CPU   16000000
#include <avr/io.h>
#include <util/delay.h>
#include <pololu/orangutan.h>
#include "io_defs.h"
#include "modules.h"

int main(void){
    //setup
    led_hb_init();
    float x;
    float x_dot;
    float phi;
    float phi_dot;
    
    float uRef;

    float K[4] = {-10.4113, -2.5702, -0.8970, -1.5861};

    while(1){
        led_hb();

        //acquire states
        x = trans_getX();
        x_dot = trans_getXDot();
        phi = orient_getPhi();
        phi_dot = orient_getPhiDot();

        //calculates new current reference
        uRef = (phi * K[0]) + (phi_dot * K[1]) + (x * K[2]) + (x_dot * K[3]);

        //pass uRef (torque) to pid motor controller
        motor_update_pid(uRef);
    }
    return 0;
}
