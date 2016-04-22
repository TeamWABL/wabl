/*
 *
 * @file    modules.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-23 01:09:46
 * @edited  2016-04-21 21:42:54
 */

#ifndef MODULES_H
#define MODULES_H

/******************************************************************************/
/* Custom Modules                                                             */
/******************************************************************************/
#include "motor/motor.h"
#include "orientation/orient.h"
#include "computer_interface/computer_interface.h"
#include "lqr/lqr.h"
#include "encoder/encoder.h"
#include "safety/safety.h"
#include "sound/sound.h"

/******************************************************************************/
/* Local Libraries                                                            */
/******************************************************************************/
#include "../libs/i2cmaster/i2cmaster.h"
#include "../libs/avr-systimer/tmr.h"
#include "../libs/ringbuffer/ringbuffer.h"
//#include "../libs/avr-uart/uart.h"

#endif //MODULES_H
