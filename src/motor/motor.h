/**
 *
 * @file    motor.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-26 03:49:13
 * @edited  2015-05-11 00:10:11
 */

#ifndef MOTOR_H
#define MOTOR_H

double motor_pid(double torqueRef,unsigned char motor);
double get_current_value(double raw);

#endif //MOTOR_H
