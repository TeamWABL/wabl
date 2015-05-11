/**
 * WABL Linear Quadratic Regulator
 * @file    lqr.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:33
 * @edited  2015-05-10 22:12:17
 */

#ifndef LQR_H
#define LQR_H

#include "lqr.h"

float lqr(float positionRef_mm, float position_mm, float velocity_mm_s, float angle_mrad, float a_velocity_mrad_s);

#endif //LQR_H
