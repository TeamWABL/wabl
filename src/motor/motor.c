/**
 * 
 * @file    motor.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-26 03:49:09
 * @edited  2015-04-28 20:18:02
 */

#include <pololu/orangutan.h>

double motor_update_pid_A(float torqueRef){
	double temp = 20.2;	
	return temp;
	float KmA = .694;	//Need to find this value
	int A = 0;
	float Kp = 200;	//These need to be changed
	float Ki = 50;
	float Kd = 0;
	static float ITermA_sum = 0;
	static float DTermA1 = 0;
	static float Motor_Temp = 0;
	
	float currentRefA = torqueRef/KmA;
	float errorA = currentRefA - CMD_GET_M1_CURRENT; 
	float PTermA = Kp * errorA;
	ITermA_sum += errorA;
	float ITermA = ITermA_sum * Ki;
	float DTermA0 = Kd * (DTermA1-errorA);
	DTermA1 = errorA;
	float Motor_Speed_A = Motor_Temp - (PTermA + ITermA + DTermA0);
	Motor_Temp = Motor_Speed_A;
	//x2_set_motor(A,0,Motor_Speed_A);
	return Motor_Speed_A;
}

void motor_update_pid_B(float torqueRef){
    float KmB = 1;	//Need to find this value
    int B = 1;
    float Kp = 1;   //These need to be changed
    float Ki = 1;
    float Kd = 1;
    static float ITermB_sum = 0;
    static float DTermB1 = 0;

    float currentRefB = torqueRef/KmB;
    float errorB = currentRefB - CMD_GET_M2_CURRENT;
    float PTermB = Kp * errorB;
    ITermB_sum += errorB;
    float ITermB = ITermB_sum * Ki;
    float DTermB0 = Kd * (DTermB1-errorB);
    DTermB1 = errorB;
    float Motor_Speed_B = PTermB + ITermB + DTermB0;
    x2_set_motor(B,0,Motor_Speed_B);
}
