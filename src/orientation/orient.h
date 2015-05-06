/**
 * Orientation module for use with the Pololu AltIMU-10 v4
 * @file    orient.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 10:19:26
 * @edited  2015-05- 6 01:14:05
 */

#ifndef ORIENT_H
#define ORIENT_H

//Gyroscope addresses
#define GYRO_ADDR (0b1101010 << 1)
//SFRs
#define LOW_ODR     0x39
#define CTRL_REG1   0x20
#define CTRL_REG4   0x23
//Output
#define GYRO_X_L    0x28
#define GYRO_X_H    0x29

/**
 * Initialize orientation sensor over the i2c bus
 */
void orient_init(void);

/**
 * Calibrate phi to account for gyro drift
 */
void orient_calibrate(void);

/**
 * @return  The raw gyro value for the x-axis
 */
int16_t orient_get_phi_dot_raw(void);

float orient_get_phi_dot(void);

/*********************************************************
 * GYRO FUNCTIONS
 * ******************************************************/

/**
 * @brief   Write value to register
 * @param   dev_addr    I2C device address
 * @param   reg_addr    Register address
 * @param   value       Value to write to register
 */
void orient_gyro_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t value);

/**
 * @brief   Read and combine high and low register from the gyro
 * @param   dev_addr    I2C device address
 * @param   reg_addr_l  Address of the the low register
 * @return  Value of low register combined with high register
 */
int16_t orient_gyro_read_reg16(uint8_t dev_addr, uint8_t reg_addr_l);

#endif //ORIENT_H
