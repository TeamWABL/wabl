/**
 * Orientation module for use with the Pololu AltIMU-10 v4
 * @file    orient.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 10:19:26
 * @edited  2015-05-10 15:09:54
 */

#ifndef ORIENT_H
#define ORIENT_H

//Gyroscope addresses
#define GYRO_ADDR (0b1101010 << 1)
//SFRs
#define GYRO_LOW_ODR     0x39
#define GYRO_CTRL_REG1   0x20
#define GYRO_CTRL_REG4   0x23
//Output
#define GYRO_X_L    0x28
#define GYRO_X_H    0x29

//Accelerometer addresses
#define ACCL_ADDR (0b0011110 << 1)

//SFRs
#define ACCL_CTRL_REG1  0x20
#define ACCL_CTRL_REG2  0x21
#define ACCL_CTRL_REG5  0x24
#define ACCL_CTRL_REG6  0x25
#define ACCL_CTRL_REG7  0x26

//Output
#define ACCL_Y_L        0x2A
#define ACCL_Y_H        0x2B
#define ACCL_Z_L        0x2C
#define ACCL_Z_H        0x2D

/**
 * Initialize orientation sensor over the i2c bus
 */
void orient_init(void);

/**
 * Calibrate phi to account for gyro drift
 */
void orient_calibrate(void);

/**
 * @brief   Update orientation values
 * @param   delta_t_ms  Time since calling function last (delta_t)
 */
void orient_update(uint8_t delta_t_ms);

/**
 * @return  Angular velocity in gyro raw units
 */
double orient_get_phi_dot_raw(void);

/**
 * @return  Angular velocity (phi_dot) in milliradians/second
 */
double orient_get_phi_dot(void);

/**
 * @return  Angle (phi) in gyro raw units
 */
double orient_get_phi_raw(void);

/**
 * @return  Angle (phi) in milliradians
 */
double orient_get_phi(void);

/*********************************************************
 * GYRO FUNCTIONS
 * ******************************************************/

/**
 * @brief   Write value to register
 * @param   dev_addr    I2C device address
 * @param   reg_addr    Register address
 * @param   value       Value to write to register
 */
void orient_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t value);

/**
 * @brief   Read and combine high and low register
 * @param   dev_addr    I2C device address
 * @param   reg_addr_l  Address of the the low register
 * @return  Value of low register combined with high register
 */
int16_t orient_read_reg16(uint8_t dev_addr, uint8_t reg_addr_l);

#endif //ORIENT_H
