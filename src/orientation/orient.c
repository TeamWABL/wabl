/**
 * Orientation module for use with the Pololu AltIMU-10 v4
 * @file    orient.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 10:19:19
 * @edited  2015-05- 4 22:10:41
 */

#define F_CPU   20000000
#include <util/delay.h>

#include "../../libs/i2cmaster/i2cmaster.h"
#include "orient.h"

/**********************************
 * Variables
 *********************************/
float phi;
float phi_dot;
//TODO make system timer based
float orient_time_step = .001;

void orient_init(void){
    phi = 0;
    phi_dot = 0;
}

void orient_calibrate(void){
    //TODO Use accelerometer? and compass to establish absolute point of reference
}

//float orient_getPhi(void){
//    phi += phi_dot * orient_time_step;
//    return phi;
//}

float orient_get_phi_dot_raw(void){
    float phi_dot_raw;
    return phi_dot_raw;
}

float orient_get_phi_dot(void){
    float phi_dot;
    return phi_dot;
}
