/**
 * 
 * @file    led.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-25 22:38:53
 * @edited  2015-03-25 23:00:47
 */

#include "led.h"

/**
 * Configure heartbeat led as an output
 */
void led_hb_init(void){
    LED_HB_DDR |= LED_HB_NUM;
}

/**
 * Toggle heartbeat led
 */
void led_hb(void){
    LED_HB_PORT ^= LED_HB_NUM;
}
