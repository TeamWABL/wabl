/**
 * 
 * @file    motor.c
 * @author  Andrew Krock
 * @date    2015-03-26 03:49:09
 * @edited  2015-05-11 00:10:09
 */

#include <pololu/orangutan.h>
#include <stdio.h>

#include "motor.h"

//PID Multipliers
double Kp = 100;
double Ki = 0;
double Kd = 0;

//Initializing PID terms
double PTerm = 0;
double ITerm = 0;
double DTerm = 0;

//Variables used to find current error
double Km = 0;
double currentRef = 0;
double currentMeasured = 0;
double error = 0;
double raw = 0;

//Max and min vals
double max_val = 255;
double min_val = -255;

//Motor
int16_t motor_speed = 0;

double motor_pid(double torqueRef,unsigned char motor){

	//Initializing holding variables
	static double sumA = 0;
	static double sumB = 0;
	static double previousA = 0;
	static double previousB = 0;

	//Printing buffer for testing 	
	char print_buf[150] = {0};
	double measured_torque = 0;


	//Finding the error depending on the motor
	if(motor == MOTOR1){
		Km = .694;
		currentRef = torqueRef/Km;
		raw = x2_get_motor_current(MOTOR1);
		currentMeasured = get_current_value(raw);
		error = currentRef - (currentMeasured);
		//measured_torque = currentMeasured * Km;
	}
	else if(motor == MOTOR2){
		Km = .710;
		currentRef = torqueRef/Km;
		raw = x2_get_motor_current(MOTOR2);
		currentMeasured = get_current_value(raw);
		error = currentRef - currentMeasured;
	}

	//PID Controller
	//Proportionl
	PTerm = Kp * error;

	//Integral
	if(motor == MOTOR1){
		sumA += error;
		if(sumA > max_val){
			sumA = max_val;
		}
		else if(sumA < min_val){
			sumA = min_val;
		}
		ITerm = sumA * Ki;
	}
	else if(motor == MOTOR2){
		sumB += error;
		if(sumB > max_val){
			sumB = max_val;
		}
		else if(sumB < min_val){
			sumB = min_val;
		}
		ITerm = sumB * Ki;
	}

	//Derivative
	if(motor == MOTOR1){
		DTerm = Kd * (error - previousA);
		previousA = error;
	}
	else if(motor == MOTOR2){
		DTerm = Kd * (error - previousB);
		previousB = error;
	}

	//Motor
	motor_speed = (PTerm + ITerm + DTerm);
	if(motor_speed > max_val){
		motor_speed = max_val;
	}
	else if(motor_speed < min_val){
		motor_speed = min_val;
	}
	//sprintf(print_buf, "Torque input = %f Current desired = %f Current measured %f error = %f Motor speed = %f Measured Torque = %f\n ", torqueRef, currentRef, currentMeasured, error, motor_speed, measured_torque);
	//sprintf(print_buf, "Torque input = %10f\t Current desired = %10f\t Current measured %10f\t error = %10f\t Motor speed = %10d\n ", torqueRef, currentRef, currentMeasured, error, motor_speed);
	//serial_send_blocking(UART0, print_buf, sizeof(print_buf));
	return motor_speed;
}

//Translate the current reading to amps
double get_current_value(double raw){
    return (((raw * 19.6) / .13) / 1000);
}
