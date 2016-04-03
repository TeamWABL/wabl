/*
 * 
 * @file    motor.c
 * @author  Andrew Krock
 * @date    2015-03-26 03:49:09
 * @edited  2016-04- 3 18:44:02
 */

#include <pololu/orangutan.h>
#include <stdio.h>
#include <string.h>

#include "motor.h"

//PID Multipliers
double Kp = 300;
double Ki = 100;
double Kd = 0;

//Motor Constants
double Km_a = .694;
double Km_b = .710;

//Variables used to find current error
//double Km = 0;	//motor constant
//double currentRef = 0;	//desired current value
//double currentMeasured = 0;	//measured current value
//double error = 0;	//calculated error
//double raw = 0;	//raw value returned by x2_get_motor_current

//Max and min vals
double max_val = 255;
double min_val = -255;

//motor "speeds"
int16_t motor_speed_a = 0;
int16_t motor_speed_b = 0;

//PID control program for the motors
//Inputs are a torque and which motor
//Output is a speed
//      double motor_pid(double torqueRef,unsigned char motor){
//      
//      	//Initializing holding variables of integral and derivative terms
//      	static double sumA = 0;
//      	static double sumB = 0;
//      	static double previousA = 0;
//      	static double previousB = 0;
//      
//      	//Printing buffer for testing 	
//      	char print_buf[150] = {0};
//      	double measured_torque = 0;
//      
//      
//      	//Finding the error depending on the motor
//      	//MOTOR1
//      	if(motor == MOTOR1){
//      		Km = .694;
//      		currentRef = torqueRef/Km;
//      		//raw = x2_get_motor_current(MOTOR1);
//      		//currentMeasured = get_current_value(raw);
//              currentMeasured = motor_get_current_a(MOTOR1);
//      		error = currentRef - (currentMeasured);
//      		//measured_torque = currentMeasured * Km;
//      	}
//      	//MOTOR2
//      	else if(motor == MOTOR2){
//      		Km = .710;
//      		currentRef = torqueRef/Km;
//      		//raw = x2_get_motor_current(MOTOR2);
//      		//currentMeasured = get_current_value(raw);
//              currentMeasured = motor_get_current_a(MOTOR2);
//      		error = currentRef - currentMeasured;
//      	}
//      
//      	//PID Controller
//      
//      	//Proportionl
//      	PTerm = Kp * error;
//      
//      	//Integral
//      	if(motor == MOTOR1){
//      		sumA += error;
//      		if(sumA > max_val){
//      			sumA = max_val;
//      		}
//      		else if(sumA < min_val){
//      			sumA = min_val;
//      		}
//      		ITerm = sumA * Ki;
//      	}
//      	else if(motor == MOTOR2){
//      		sumB += error;
//      		if(sumB > max_val){
//      			sumB = max_val;
//      		}
//      		else if(sumB < min_val){
//      			sumB = min_val;
//      		}
//      		ITerm = sumB * Ki;
//      	}
//      
//      	//Derivative
//      	if(motor == MOTOR1){
//      		DTerm = Kd * (error - previousA);
//      		previousA = error;
//      	}
//      	else if(motor == MOTOR2){
//      		DTerm = Kd * (error - previousB);
//      		previousB = error;
//      	}
//      
//      	//Setting the motor speed
//          int16_t pid_motor_speed = (PTerm + ITerm + DTerm);
//          if(pid_motor_speed > max_val){
//              pid_motor_speed = max_val;
//          }else if(pid_motor_speed < min_val){
//              pid_motor_speed = min_val;
//          }
//      //    if (motor == MOTOR1){
//      //        motor_speed_a = (PTerm + ITerm + DTerm);
//      //        if(motor_speed_a > max_val){
//      //            motor_speed_a = max_val;
//      //        }
//      //        else if(motor_speed_a < min_val){
//      //            motor_speed_a = min_val;
//      //        }
//      //    }else if (motor == MOTOR2){
//      //        motor_speed_b = (PTerm + ITerm + DTerm);
//      //        if(motor_speed_b > max_val){
//      //            motor_speed_b = max_val;
//      //        }
//      //        else if(motor_speed_b < min_val){
//      //            motor_speed_b = min_val;
//      //        }
//      //    }
//      	//sprintf(print_buf, "Torque input = %f Current desired = %f Current measured %f error = %f Motor speed = %f Measured Torque = %f\n ", torqueRef, currentRef, currentMeasured, error, motor_speed, measured_torque);
//      	//sprintf(print_buf, "Torque input = %10f\t Current desired = %10f\t Current measured %10f\t error = %10f\t Motor speed = %10d\n ", torqueRef, currentRef, currentMeasured, error, motor_speed);
//      	//serial_send_blocking(UART0, print_buf, sizeof(print_buf));
//          //if (motor == MOTOR1) return motor_speed_a;
//          //return motor_speed_b;
//          return pid_motor_speed;
//      }

int16_t motor_update_pid(uint8_t motor, double torqueRef){
    double currentRef = 0;
    double error = 0;
    double current_measured = 0;
    double Pterm = 0;
    static double Iterm_a = 0;
    static double Iterm_b = 0;
    int16_t motor_speed = 0;

    char print_buf[120];
    memset(print_buf, 0, 120);

    switch(motor){
        case MOTOR1:
            currentRef = torqueRef/Km_a;
            current_measured = motor_get_current_a(MOTOR1);

            error = currentRef - current_measured;

            //Proportional Control
            Pterm = Kp * error;

            motor_speed = /*motor_speed_a + */Pterm;
            break;
        case MOTOR2:
            currentRef = torqueRef/Km_b;
            current_measured = motor_get_current_a(MOTOR2);

            error = currentRef - current_measured;

            //Proportional Control
            Pterm = Kp * error;

            //Iterm_b += Ki * error;

            motor_speed = /*motor_speed_b + */Pterm;
            break;
        default:;
            //do nothing
    }

    if (motor_speed > 255) motor_speed = 255;
    else if (motor_speed < -255) motor_speed = -255;

    //debug printing
    //sprintf(print_buf, "torqueRef: %f\t currentRef: %f\t currentMeasured: %f\t error: %f\t speed: %d\n", torqueRef, currentRef, current_measured, error, motor_speed);
    //sprintf(print_buf, "speed: %d\n", motor_speed);
    //serial_send_blocking(UART0, print_buf, sizeof(print_buf));


    return motor_speed; 
}

void motor_set_speed(uint8_t motor, int16_t speed){
    if (motor == MOTOR1){
        motor_speed_a = speed;
    }else if (motor == MOTOR2){
        motor_speed_b = speed;
    }
    x2_set_motor(motor, IMMEDIATE_DRIVE, speed);
}

//Translate the current reading to amps
//TODO fix for voltage offset (1 corresponds to 300 mA, 2 ~440 mA) (and other issues)
double get_current_value(double raw){
    return (((raw * 19.6) / .13) / 1000);
}

double motor_get_current_ma(uint8_t motor){
    int16_t  raw_current = x2_get_motor_current(motor);

    int8_t direction = motor_get_direction(motor);

    //5000 mvolts, 256 levels (8 bit dac), .13 V/A sensitivity
    double magnitude = (raw_current * (5000.0 / 256.0))/0.13;
    
    if (magnitude == 0.0) return 0.0;
    else return direction * magnitude;
    //return direction * ();
}

double motor_get_current_a(uint8_t motor){
    return motor_get_current_ma(motor)/1000;
}

int8_t motor_get_direction(uint8_t motor){
    int16_t speed = (motor == MOTOR1 ? motor_speed_a : motor_speed_b);
    return (speed > 0) - (speed < 0);
}
