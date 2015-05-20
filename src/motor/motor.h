/**
 * PID motor controller module
 * @file    motor.h
 * @author  Andrew Krock
 * @date    2015-03-26 03:49:13
 * @edited  2015-05-19 20:54:20
 */

#ifndef MOTOR_H
#define MOTOR_H

/**
 * @brief Calculates new motor voltage
 * @param   torqueRef   Torque reference from lqr() in N*m
 * @param   motor       MOTOR1 or MOTOR2
 * @return  Motor value that corresponds to a duty cycle [-255 255]
 */
double motor_pid(double torqueRef,unsigned char motor);

/**
 * @brief   Translate the raw current reading to amps
 * @param   raw     Raw current reading
 * @return  Current in amps
 */
double get_current_value(double raw);

#endif //MOTOR_H
