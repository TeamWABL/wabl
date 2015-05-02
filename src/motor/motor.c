/**
 * 
 * @file    motor.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-26 03:49:09
 * @edited  2015-04-28 20:18:02
 */

#include <pololu/orangutan.h>

double motor_update_pid(float torqueRef,unsigned char motor){
	//float x = x2_get_motor_current(MOTOR1);
	//return (((x * 19.6) / .13) / 1000);

	//PID Constants
	float Kp = 200;
	float Ki = 50;
	float Kd = 0;
	float PTerm = 0;
	float ITerm = 0;
	float DTerm = 0;
	float error = 0;
	
	//Initializing Holding Variables
	static float sumA = 0;
	static float sumB = 0;
	static float previousA = 0;
	static float previousB = 0;
	static float motor_temp = 100;

	//Translate the current reading
	float get_current_value(float raw){
	return (((raw * 19.6) / .13) / 1000);
	}

	//Finding the error depending on the motor
	if(motor == MOTOR1){
		float Km = .694;
		float currentRef = torqueRef * (1/Km);
		float raw = x2_get_motor_current(MOTOR1);
		float currentMeasured = get_current_value(raw);
		error = currentRef - currentMeasured;
		//return error;
	}
	else if(motor == MOTOR2){
		float Km = .710;
		float currentRef = torqueRef * (1/Km);
		float raw = x2_get_motor_current(MOTOR2);
		float currentMeasured = get_current_value(raw);
		error = currentRef - currentMeasured;
	}

	//PID Controller
	//Proportional
	PTerm = Kp * error;

	//Integral
	if(motor == MOTOR1){
		sumA += error;
		ITerm = sumA * Ki;
		//return ITerm;
	}
	else if(motor == MOTOR2){
		sumB += error;
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
	float motor_speed = motor_temp - (PTerm + ITerm + DTerm);
	motor_temp = motor_speed;
	//x2_set_motor(motor,0,motor_speed);
	return motor_speed;
}
