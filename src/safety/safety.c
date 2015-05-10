/**
 * WABL's safety module
 * @file    safety.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-05-10 17:01:12
 * @edited  2015-05-10 19:41:15
 */

#include "safety.h"

uint8_t safety_battery_critical(void){
    //return true if less than 9.5 volts (critical voltage is 9 volts)
    //ADC6
    uint16_t vbat_mv = read_battery_millivolts_x2();
    uint8_t critical = (vbat_mv < CRITICAL_VOLTAGE_MV);
    return critical;
}


