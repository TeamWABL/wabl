/**
 *
 * @file    myi2c.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-05- 4 22:06:56
 * @edited  2015-05- 4 23:33:43
 */

#ifndef MYI2C_H
#define MYI2C_H

#define MYI2C_READ    0x01
#define MYI2C_WRITE   0x00

#define GYRO_ADDR   (0b1101010 << 1)

//Gyro SFRs
#define LOW_ODR     0x39
#define CTRL_REG4   0x23
#define CTRL_REG1   0x20

//Gyro output registers
#define GYRO_X_L    0x28
#define GYRO_X_H    0x29

void myi2c_init(void);
int16_t myi2c_read_x_gyro(void);

#endif //MYI2C_H
