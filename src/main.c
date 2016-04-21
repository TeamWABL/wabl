/**
 * WABL main loop
 * @file    main.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-22 20:08:47
 * @edited  2016-04-21 15:18:05
 */

#define F_CPU   20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <pololu/orangutan.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "io_defs.h"
#include "modules.h"

//testing
#include "test_code/test.h"
//testing


//globals
double a_torqueRef = 0;
double b_torqueRef = 0;

int16_t a_motor_speed = 0;
int16_t b_motor_speed = 0;
char print_buf[120];

int main(void){
    //uart setup

    uart_init();
//	char print_buf[120];

    serial_send_blocking(XBEE, "Initializing UART...", 20);
    serial_send_blocking(XBEE, "done.\n", 6);



    //state acquisition setup
    serial_send_blocking(XBEE, "Initializing state acquisition...", 33);
    double phi;
    double phi_dot;
    
    double a_x;
    double a_x_dot;
    double b_x;
    double b_x_dot;

    orient_init();
    encoder_init();

    serial_send_blocking(XBEE, "done.\n", 6);

    //lqr setup
    //position to track to in millimeters
    double positionRef_mm = 0;

    //int16_t a_motor_speed;
    //int16_t b_motor_speed;

    // timer setup
    serial_send_blocking(XBEE, "Initializing Timer...", 21);

    sysT_init();

    sysTimer16_t print_timer;
    sysT_16_init(&print_timer);

    serial_send_blocking(XBEE, "done.\n", 6);

    sei();

    while(1){
        if (!safety_battery_critical()){
            safety_led_toggle();
            //clear print buf
            memset(print_buf, 0, 120);

            //acquire state variables
            phi = orient_get_phi();
            phi_dot = orient_get_phi_dot();
            
            a_x = encoder_get_x(MOTOR1);
            a_x_dot = encoder_get_x_dot(MOTOR1);

            //      b_x = encoder_get_x(MOTOR2);
            //      b_x_dot = encoder_get_x_dot(MOTOR2);

            a_torqueRef = lqr(positionRef_mm, a_x, a_x_dot, phi, phi_dot);
            //      b_torqueRef = lqr(positionRef_mm, b_x, b_x_dot, phi, phi_dot);
            //a_torqueRef = 0.5;

            //set motors
            //motor_set_speed(MOTOR1, a_motor_speed);
            //motor_set_speed(MOTOR2, b_motor_speed);
            //motor_set_speed(MOTOR2, b_motor_speed);

            //sprintf(print_buf, "phi = %10f, phi_raw = %10f, phi_dot = %10f, phi_dot_raw = %10f\n", phi, phi_raw, phi_dot, phi_dot_raw);	
            //sprintf(print_buf, "phi = %10f, phi_dot = %10f, b_x = %10f, b_x_dot = %10f\n", phi, phi_dot, b_x, b_x_dot);	
            //sprintf(print_buf, "%f\n", phi);	
            //sprintf(print_buf, "A:%10f\tB:%10f\n", a_torqueRef, b_torqueRef);	
            //sprintf(print_buf, "A:%10d\tB:%10d\n", a_motor_speed, b_motor_speed);	
            //sprintf(print_buf, "Phi: %10f\tX: %10f\tTorque: %10f\tSpeed: %10d\n", phi, a_x, a_torqueRef, a_motor_speed);
            //serial_send_blocking(XBEE, print_buf, sizeof(print_buf));
            //serial_send_blocking(XBEE, "testing\n", sizeof("testing\n"));
            //motor_update_pid_B(uRef);
            

            
            ////serial_send_blocking(XBEE, "hi \n", sizeof("hi \n"));
            ////x2_set_motor(MOTOR1, IMMEDIATE_DRIVE, -255);
            //motor_set_speed(MOTOR1, -255);
            ////int current = x2_get_motor_current(MOTOR1);
            //double current = motor_get_current_ma(MOTOR1);
            //int direction = motor_get_direction(MOTOR1);
            //sprintf(print_buf, "current: %f\t direction: %d\n", current, direction);
            //sprintf(print_buf, "%d\n", b_x);
            //motor_set_speed(MOTOR2, 255);
            //sprintf(print_buf, "%f\n", orient_get_phi());
            //serial_send(XBEE, print_buf, sizeof(print_buf));
            //delay_ms(200);
            //delay_ms(200);


            //int16_t speed = motor_update_pid(MOTOR1, 0.2082);
            //motor_set_speed(MOTOR1, speed);

            // sprintf(print_buf, "current: %f\t speed: %d\n", motor_get_current_a(MOTOR1), speed);
            // serial_send_blocking(XBEE, print_buf, sizeof(print_buf));
            //x2_set_motor(MOTOR2, IMMEDIATE_DRIVE, 255);
            //x2_set_motor(0x00, 0x00, 255);
            //x2_set_motor(0x01, 0x00, 255);
            //set_motors(255,255);
            //serial_send_blocking(XBEE, "done. \n", sizeof("done. \n"));
            sprintf(print_buf, "%f\n", orient_get_phi());
            serial_send(XBEE, print_buf, sizeof(print_buf));
            delay_ms(10);
        }else{
            //player critical battery melody
            sound_play_melody(BATTERY_CRITICAL);
            //wait for the melody to finish playing
            while(is_playing());
            cli();
            //exit infinite loop
            break;
        }
    }
    return 0;
}

//1ms timer interrupt
ISR(TIMER1_COMPA_vect){
    static uint8_t orient_update_tmr;
    static uint8_t motor_update_tmr;
    //static uint16_t print_tmr;
    
    //cli();

    yellow_led(true);
    //650 uS process
    if (++orient_update_tmr == 5){
        orient_update_tmr = 0;
        orient_update(5);
        encoder_update(5);
    }

    //b_torqueRef = 0.7;
    if (++motor_update_tmr == 2){
    motor_update_tmr = 0;
    //110 uS process
        a_motor_speed = motor_update_pid(MOTOR1, a_torqueRef);
        //b_motor_speed = motor_update_pid(MOTOR2, b_torqueRef);
        motor_set_speed(MOTOR1, a_motor_speed);
        motor_set_speed(MOTOR2, a_motor_speed);
    }
    //sei();

    //sysT_timer_service();
    yellow_led(false);
}
