/**
 * 
 * @file    encoder.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 20:19:10
 * @edited  2015-05- 7 02:02:31
 */

#include <pololu/orangutan.h>

#include "encoder.h"

//(pi*156mm)/720 pulses
double count2mmeter = 0.680678408277789;

void encoder_init(void){
    //TODO rearrange to get expect forward and backward values
    encoders_init(IO_D4, IO_D5, IO_D6, IO_D7);
}

int encoder_get_x_raw(unsigned char motor){
    int count = 0;

    switch (motor){
        case MOTOR1:
            count = encoders_get_counts_m1();
            break;
        case MOTOR2:
            count = encoders_get_counts_m2();
            break;
        default:
            break;
    }
    return count;
}

double encoder_get_x(unsigned char motor){
    int count = encoder_get_x_raw(motor);
    double x = count2mmeter * count;
    return x;
}
