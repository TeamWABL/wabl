/**
 *
 * @file    encoder.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 20:19:15
 * @edited  2015-05-10 21:44:55
 */

#ifndef ENCODER_H
#define ENCODER_H

/**
 * @brief Setup encoder pins
 */
void encoder_init(void);

void encoder_update(uint8_t delta_t_ms);

double encoder_get_x(unsigned char motor);

double encoder_get_x_dot(unsigned char motor);

#endif //ENCODER_H
