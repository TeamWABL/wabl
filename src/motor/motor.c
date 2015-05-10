/**
 * 
 * @file    motor.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-26 03:49:09
 * @edited  2015-04-28 20:18:02
 */

#include <pololu/orangutan.h>
#include <stdio.h>

//PID Multipliers
float Kp = 100;
float Ki = 0;
float Kd = 0;

//Initializing PID terms
float PTerm = 0;
float ITerm = 0;
float DTerm = 0;

//Variables used to find current error
float Km = 0;
float currentRef = 0;
float currentMeasured = 0;
float error = 0;
float raw = 0;

//Max and min vals
float max_val = 255;
float min_val = -255;

//Motor
float motor_speed = 0;

double motor_update_pid(float torqueRef,unsigned char motor){

	//Initializing holding variables
	static float sumA = 0;
	static float sumB = 0;
	static float previousA = 0;
	static float previousB = 0;

	//Printing buffer for testing 	
	char print_buf[150];
	float measured_torque = 0;

	//Translate the current reading to amps
	float get_current_value(float raw){
		return (((raw * 19.6) / .13) / 1000);
	}

	//Finding the error depending on the motor
	if(motor == MOTOR1){
		Km = .694;
		currentRef = torqueRef/Km;
		raw = x2_get_motor_current(MOTOR1);
		currentMeasured = get_current_value(raw);
		error = currentRef - (currentMeasured);
		measured_torque = currentMeasured * Km;
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
	//serial_send_blocking(UART0, print_buf, sizeof(print_buf));
	x2_set_motor(motor, IMMEDIATE_DRIVE, motor_speed);
	return 0;
}




