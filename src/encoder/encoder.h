/**
 * Motor quadrature encoder module
 * @file    encoder.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 20:19:15
 * @edited  2015-05-19 23:32:05
 */

#ifndef ENCODER_H
#define ENCODER_H

/**
 * @brief Setup encoder pins, must be called once
 */
void encoder_init(void);

/**
 * @brief Calculate new position (x) and velocity (x_dot) values
 * @param   delta_t_ms  Time difference since last call in milliseconds
 */
void encoder_update(uint8_t delta_t_ms);

/**
 * @brief Get position (x) for specified motor in millimeters
 * @param   motor   MOTOR1 or MOTOR2
 * @return  position (x) in millimeters
 */
double encoder_get_x(unsigned char motor);

/**
 * @brief Get velocity (x_dot) for specified motor in millimeters/second
 * @param   motor   MOTOR1 or MOTOR2
 * @return  velocity (x) in millimeters/second
 */
double encoder_get_x_dot(unsigned char motor);

#endif //ENCODER_H
