/*
 * 
 * @file    encoder.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 20:19:10
 * @edited  2016-04- 3 19:23:09
 */

#include <pololu/orangutan.h>

#include "encoder.h"

//(pi*156mm)/720 pulses
double count2mmeter = 0.680678408277789;

//motor A/1 variables
double a_x_raw;
double a_x;
double a_x_dot_raw;
double a_x_dot;
double a_previous_x_raw;

//motor B/2 variables
double b_x_raw;
double b_x;
double b_x_dot_raw;
double b_x_dot;
double b_previous_x_raw;

void encoder_init(void){
    //pololu function that sets which io pins correspond to which motors/phases
    encoders_init(IO_D5, IO_D4, IO_D6, IO_D7);

    //motor A/1 variables
    a_x_raw = 0;
    a_x = 0;
    a_x_dot_raw = 0;
    a_x_dot = 0;
    a_previous_x_raw = 0;

    //motor B/2 variables
    b_x_raw = 0;
    b_x = 0;
    b_x_dot_raw = 0;
    b_x_dot = 0;
    b_previous_x_raw = 0;
}

void encoder_update(uint8_t delta_t_ms){
    //save previous values
    a_previous_x_raw = a_x_raw;
    b_previous_x_raw = b_x_raw;

    //get new x values
    a_x_raw = encoders_get_counts_m1();
    b_x_raw = encoders_get_counts_m2();

    //convert new x values to millimeters
    a_x = a_x_raw * count2mmeter;
    b_x = b_x_raw * count2mmeter;
    //b_x = 501;

    //calculate raw velocities
    //multiply by 1000 to account for milliseconds (results in ticks/second)
    a_x_dot_raw = (((a_x_raw - a_previous_x_raw) * 1000) / delta_t_ms);
    b_x_dot_raw = (((b_x_raw - b_previous_x_raw) * 1000) / delta_t_ms);

    //convert new velocities to millimeters/second
    a_x_dot = a_x_dot_raw * count2mmeter;
    b_x_dot = b_x_dot_raw * count2mmeter;
    //b_x_dot = 3.14;
}

double encoder_get_x(unsigned char motor){
    if (motor == MOTOR1){
        return a_x;
    }else if (motor == MOTOR2){
        return b_x;
    }
    else{
        return 0;
    }
}

double encoder_get_x_dot(unsigned char motor){
    if (motor == MOTOR1){
        return a_x_dot;
    }else if (motor == MOTOR2){
        return b_x_dot;
    }
    else{
        return 0;
    }
}
