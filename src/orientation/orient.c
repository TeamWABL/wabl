/**
 * Orientation module for use with the Pololu AltIMU-10 v4
 * @file    orient.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 10:19:19
 * @edited  2015-05- 6 01:32:04
 */

#define F_CPU   20000000
#include <util/delay.h>

#include "../../libs/i2cmaster/i2cmaster.h"
#include "orient.h"

/**********************************
 * Variables
 *********************************/
void orient_init(void){
    //initialize i2cmaster library
    i2c_init();

    //low speed ODR disabled
    orient_gyro_write_reg(GYRO_ADDR, LOW_ODR, 0x00);

    //(+/- 245 degrees/second full scale)
    orient_gyro_write_reg(GYRO_ADDR, CTRL_REG4, 0x00);

    //0x69 = 0b01101001
    //DR = 01 (200 Hz ODR); BW = 10 (50 Hz bandwidth); PD = 1 (normal mode); Zen = 0; Yen = 0; Xen = 1
    orient_gyro_write_reg(GYRO_ADDR, CTRL_REG1, 0x69);
}

void orient_calibrate(void){
    //TODO Use accelerometer? and compass to establish absolute point of reference
}


//float orient_getPhi(void){
//    phi += phi_dot * orient_time_step;
//    return phi;
//}

int16_t orient_get_phi_dot_raw(void){
    int16_t phi_dot_raw = orient_gyro_read_reg16(GYRO_ADDR, GYRO_X_L);
    return phi_dot_raw;
}

float orient_get_phi_dot(void){
    float phi_dot = 5;
    return phi_dot;
}

/*********************************************************
 * GYRO FUNCTIONS
 * ******************************************************/
void orient_gyro_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t value){
    i2c_start_wait(dev_addr + I2C_WRITE);

    i2c_write(reg_addr);
    i2c_write(value);

    i2c_stop();
}

int16_t orient_gyro_read_reg16(uint8_t dev_addr, uint8_t reg_addr_l){
    i2c_start_wait(dev_addr + I2C_WRITE);

    i2c_write(reg_addr_l | (1<<7));

    i2c_rep_start(dev_addr + I2C_READ);
    uint8_t output_l = i2c_readAck();
    uint8_t output_h = i2c_readNak();

    i2c_stop();

    int16_t ret = (output_h << 8) | output_l;

    return ret;
}
