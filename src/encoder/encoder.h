/**
 *
 * @file    encoder.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 20:19:15
 * @edited  2015-04-28 23:46:12
 */

#ifndef ENCODER_H
#define ENCODER_H

/**
 * @brief Setup encoder pins
 */
void encoder_init(void);

/**
 * @brief Get the raw encoder value
 * @param   motor   MOTOR1, MOTOR2
 * @return  Raw encoder ticks
 */
int encoder_get_x_raw(unsigned char motor);

/**
 * @brief Get the x position of the wheels in mm
 * @param   motor   MOTOR1, MOTOR2
 * @return  x position in mm
 */
double encoder_get_x(unsigned char motor);

#endif //ENCODER_H
