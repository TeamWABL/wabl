/**
 * 
 * @file    test.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-21 19:47:34
 * @edited  2015-04-22 00:45:21
 */
#include <pololu/orangutan.h>
#include "../modules.h"

#include "test.h"

void test_motor(void){
    x2_set_motor(0, 0, 20);
    delay_ms(200);
    x2_set_motor(0, 0xff, 20);
    delay_ms(1);

    x2_set_motor(0, 0, -20);
    delay_ms(200);
    x2_set_motor(0, 0xff, 255);
    delay_ms(1);
}

void test_i2c(void){
    i2c_start(0x55);
    i2c_write(0x00);
}
