/*
 * Orientation module for use with the Pololu AltIMU-10 v4
 * @file    orient.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 10:19:19
 * @edited  2015-05-19 20:54:41
 */

#define F_CPU   20000000
#include <pololu/orangutan.h>
#include <stdio.h>

#include "../../libs/i2cmaster/i2cmaster.h"
#include "orient.h"

/**********************************
 * Variables
 *********************************/
double raw2mdegrees = 8.75;
double raw2mradians = 0.152716309549504;

//int16_t bias_offset = -142;
//int16_t bias_offset = -53;
//double bias_offset = -89.88;
double bias_offset = -74.4;
double scale_factor = 0.931252477644701;

double phi_raw;
double phi;
double phi_dot_raw;
double phi_dot;
double previous_phi_dot_raw;

/**********************************
 * Library Functions
 *********************************/
void orient_init(void){
    //initialize i2cmaster library
    i2c_init();

    //low speed ODR disabled
    orient_write_reg(GYRO_ADDR, GYRO_LOW_ODR, 0x00);

    //(+/- 245 degrees/second full scale)
    orient_write_reg(GYRO_ADDR, GYRO_CTRL_REG4, 0x00);

    //0x69 = 0b01101001
    //DR = 01 (200 Hz ODR); BW = 10 (50 Hz bandwidth); PD = 1 (normal mode); Zen = 0; Yen = 0; Xen = 1
    orient_write_reg(GYRO_ADDR, GYRO_CTRL_REG1, 0x69);

    orient_calibrate();

    //this assumes starting on kick stand for calibration
    phi_raw = -1167;
    phi = -178.2;
    phi_dot_raw = 0;
    phi_dot = 0;
    previous_phi_dot_raw = 0;
}

void orient_calibrate(void){
    //TODO Use accelerometer to establish absolute point of reference
    char buff[100] = {0};
    int32_t summed_offset = 0; //TODO is this overflowing?
    uint16_t samples = 0;
    for (samples = 0; samples < 100; samples++){
        summed_offset += orient_read_reg16(GYRO_ADDR, GYRO_X_L);
        //delay_ms(100);
        //won't functio without this?
        printf(buff, "%ld\n", summed_offset);
        serial_send_blocking(UART0, buff, sizeof(buff));
        //leave it
    }
    bias_offset = -1.0 * ((double)summed_offset/((double)samples));
    sprintf(buff, "Summed: %ld Samples: %d Bias: %f\n", summed_offset, samples, bias_offset);
    serial_send_blocking(UART0, buff, sizeof(buff));
}


//float orient_getPhi(void){
//    phi += phi_dot * orient_time_step;
//    return phi;
//}

void orient_update(uint8_t delta_t_ms){
    //store previous values
    previous_phi_dot_raw = phi_dot_raw;

    //calculate new phi_dot
    //read gyro value and apply bias offset
    phi_dot_raw = orient_read_reg16(GYRO_ADDR, GYRO_X_L) + bias_offset;
    phi_dot = phi_dot_raw * raw2mradians;

    //calculate new phi
    //phi_raw += (scale_factor * delta_t_ms * ((phi_dot_raw + previous_phi_dot_raw)/2))/1000;
    //phi = phi_raw * raw2mradians;
    phi_raw += (scale_factor * delta_t_ms * ((phi_dot_raw + previous_phi_dot_raw)/2))/1000;
    //phi_raw = (phi_raw < 1) ? 0 : phi_raw;
    phi = phi_raw * raw2mradians;
}

double orient_get_phi_dot_raw(void){
    return phi_dot_raw;
}

double orient_get_phi_dot(void){
    return phi_dot;
}

double orient_get_phi_raw(void){
    return phi_raw;
}

double orient_get_phi(void){
    return phi;
}

/*********************************************************
 * GYRO FUNCTIONS
 * ******************************************************/
void orient_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t value){
    i2c_start_wait(dev_addr + I2C_WRITE);

    i2c_write(reg_addr);
    i2c_write(value);

    i2c_stop();
}

int16_t orient_read_reg16(uint8_t dev_addr, uint8_t reg_addr_l){
    i2c_start_wait(dev_addr + I2C_WRITE);

    i2c_write(reg_addr_l | (1<<7));

    i2c_rep_start(dev_addr + I2C_READ);
    uint8_t output_l = i2c_readAck();
    uint8_t output_h = i2c_readNak();

    i2c_stop();

    int16_t ret = (output_h << 8) | output_l;

    return ret;
}
