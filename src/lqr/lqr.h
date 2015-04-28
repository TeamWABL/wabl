/**
 * WABL Linear Quadratic Regulator
 * @file    lqr.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:33
 * @edited  2015-04-28 15:00:17
 */

#ifndef LQR_H
#define LQR_H

#include "lqr.h"

float lqr_update(float positionRef, float position, float velocity, float angle, float a_velocity);

#endif //LQR_H
