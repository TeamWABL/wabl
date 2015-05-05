/**
 *
 * @file    modules.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-23 01:09:46
 * @edited  2015-05- 4 23:27:47
 */

#ifndef MODULES_H
#define MODULES_H

/******************************************************************************/
/* Custom Modules                                                             */
/******************************************************************************/
#include "led/led.h"
#include "motor/motor.h"
#include "orientation/orient.h"
#include "uart/uart.h"
#include "lqr/lqr.h"
#include "encoder/encoder.h"
#include "myi2c/myi2c.h"

/******************************************************************************/
/* Local Libraries                                                            */
/******************************************************************************/
#include "../libs/i2cmaster/i2cmaster.h"
#include "../libs/avr-systimer/tmr.h"

#endif //MODULES_H
