/**
 * Orientation module for use with the Pololu AltIMU-10 v4
 * @file    orient.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 10:19:26
 * @edited  2015-03-26 03:48:27
 */

#ifndef ORIENT_H
#define ORIENT_H

/**
 * Initialize orientation sensor over the i2c bus
 */
void orient_init(void);

/**
 * Calibrate phi to account for gyro drift
 */
void orient_calibrate(void);

/**
 * @return  The angle of the pendulum in radians
 */
float orient_getPhi(void);
/**
 * @return  The angular velocity of the pendulum in radians/s
 */
float orient_getPhiDot(void);

#endif //ORIENT_H
