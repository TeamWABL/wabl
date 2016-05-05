/**
 * WABL Linear Quadratic Regulator
 * @file    lqr.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:33
 * @edited  2016-05- 3 23:25:01
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

/**
 * @brief   Set new lqr phi constant
 * @param   new_k_phi   New phi constant
 */
void lqr_set_k_phi(double new_k_phi);

/**
 * @brief   Set new lqr phi_dot constant
 * @param   new_k_phi_dot   New phi_dot constant
 */
void lqr_set_k_phi_dot(double new_k_phi_dot);

/**
 * @brief   Set new lqr x constant
 * @param   new_k_x   New x constant
 */
void lqr_set_k_x(double new_k_x);

/**
 * @brief   Set new lqr x_dot constant
 * @param   new_k_x_dot   New x_dot constant
 */
void lqr_set_k_x_dot(double new_k_x_dot);

#endif //LQR_H
