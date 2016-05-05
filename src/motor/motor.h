/**
 * PID motor controller module
 * @file    motor.h
 * @author  Andrew Krock
 * @date    2015-03-26 03:49:13
 * @edited  2016-05- 3 22:38:04
 */

#ifndef MOTOR_H
#define MOTOR_H

//      /**
//       * @brief Calculates new motor voltage
//       * @param   torqueRef   Torque reference from lqr() in N*m
//       * @param   motor       MOTOR1 or MOTOR2
//       * @return  Motor value that corresponds to a duty cycle [-255 255]
//       */
//      double motor_pid(double torqueRef,unsigned char motor);

int16_t motor_update_pid(uint8_t motor, double torqueRef);

/**
 * @brief   Translate the raw current reading to amps
 * @param   raw     Raw current reading
 * @return  Current in amps
 */
double get_current_value(double raw);

/**
 * @brief   Update motor "speed"
 * @param   motor   MOTOR1 or MOTOR2 (motor to update)
 * @param   speed   Value from -255 to 255 that corresponds to the duty cycle applied to the motor
 */
void motor_set_speed(uint8_t motor, int16_t speed);

/**
 * Set a new value for the proportional PID constant
 * @param   new_kp  Value to set the proportional constant to
 */
void motor_set_kp(double new_kp);

/**
 * Set a new value for the integral PID constant
 * @param   new_ki  Value to set the integral constant to
 */
void motor_set_ki(double new_ki);

/**
 * @brief   Get the current draw of a motor in milliamps
 * @param   motor   MOTOR1 or MOTOR2
 * @return  Current in milliamps
 */
double motor_get_current_ma(uint8_t motor);

/**
 * @brief   Get the current draw of a motor in amps
 * @param   motor   MOTOR1 or MOTOR2
 * @return  Current in amps
 */
double motor_get_current_a(uint8_t motor);

/**
 * @brief   Find direction motor is travelling
 * @param   motor   MOTOR1 or MOTOR2
 * @return  1 for forward, 0 for stationary, -1 for backward
 */
int8_t motor_get_direction(uint8_t motor);

#endif //MOTOR_H
