/**
 * 
 * @file    motor.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-26 03:49:09
 * @edited  2015-03-26 03:51:16
 */

#include <pololu/orangutan.h>

void motor_update_pid_A(float torqueRef){
	float KmA = 1;	//Need to find this value
	int A = 0;
	float Kp = 1;	//These need to be changed
	float Ki = 1;
	float Kd = 1;
	static float ITermA_sum = 0;
	static float DTermA1 = 0;
	
	float currentRefA = torqueRef/KmA;
	float errorA = currentRefA - getMotorCurrent(A);
	float PTermA = Kp * errorA;
	ITermA_sum += errorA;
	float ITermA = ITermA_sum * Ki;
	float DTermA0 = Kd * (DTermA1-errorA);
	DTermA1 = errorA;
	float Motor_Speed_A = PTermA + ITermA + DTermA0;
	setMotor(A,0,Motor_Speed_A);
}

void motor_update_pid(float torqueRef){
    float KmB = 1;	//Need to find this value
    int B = 1;
    float Kp = 1;   //These need to be changed
    float Ki = 1;
    float Kd = 1;
    static float ITermB_sum = 0;
    static float DTermB1 = 0;

    float currentRefB = torqueRef/KmB;
    float errorB = currentRefB - getMotorCurrent(B);
    float PTermB = Kp * errorB;
    ITermB_sum += errorB;
    float ITermB = ITermB_sum * Ki;
    float DTermB0 = Kd * (DTermB1-errorB);
    DTermB1 = errorB;
    float Motor_Speed_B = PTermB + ITermB + DTermB0;
    setMotor(B,0,Motor_Speed_B);
}

