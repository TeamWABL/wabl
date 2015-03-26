/**
 * 
 * @file    trans.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 11:00:47
 * @edited  2015-03-25 23:59:32
 */

#include <pololu/orangutan.h>
#include "trans.h"

/*********************************
 * Variables
 ********************************/

//TODO setup ring buffer
float x;
float x_old;
float x_dot;
float count_to_meters = .0002700897;
float trans_time_step = .001; //TODO make system timer based


/********************************
 * Functions
 *******************************/

void trans_init(void){
    //encoders_init();
}

void trans_resetX(void){
    x = 0;
    encoders_get_counts_and_reset_m1();
}

float trans_getX(void){
    x_old = x;
    x = encoders_get_counts_m1() * count_to_meters;
    return x;
}

float trans_getXDot(void){
    x_dot = (x - x_old) / trans_time_step;
    return x_dot;
}
