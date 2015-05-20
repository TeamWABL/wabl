/**
 *
 * @file    safety.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-05-10 17:01:17
 * @edited  2015-05-19 21:03:00
 */

#ifndef SAFETY_H
#define SAFETY_H

#include <pololu/orangutan.h>

//Analog pin that is 5/16 the battery voltage
#define BATLEV  ADC6

//10 volt cutoff for 3S LiPO (9 volt is critical voltage)
///Battery's critical voltage
#define CRITICAL_VOLTAGE_MV   10000

/**
 * @brief   Checks if battery voltage is at its critical level
 * @return  True if battery level is critical, false if not
 */
uint8_t safety_battery_critical(void);

#endif //SAFETY_H
