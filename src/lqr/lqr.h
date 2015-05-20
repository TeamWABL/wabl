/**
 * WABL Linear Quadratic Regulator
 * @file    lqr.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:33
 * @edited  2015-05-19 20:45:58
 */

#ifndef LQR_H
#define LQR_H

#include "lqr.h"

/**
 * @brief Calculate new torque reference from system states
 * @param   positionRef_mm  Position to track to in millimeters
 * @param   position_mm         System state: position (x) in millimeters
 * @param   velocity_mm_s       System state: velocity (x_dot) in millimeters/second
 * @param   angle_mrad          System state: pendulum angle (phi) in milliradians
 * @param   a_velocity_mrad_s   System state: pendulum angular velocity (phi_dot) in milliradians/second
 * @return  New torque reference in N*m
 */
float lqr(float positionRef_mm, float position_mm, float velocity_mm_s, float angle_mrad, float a_velocity_mrad_s);

#endif //LQR_H
