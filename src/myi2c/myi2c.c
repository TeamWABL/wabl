/**
 * 
 * @file    myi2c.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-05- 4 22:06:52
 * @edited  2015-05- 4 23:30:08
 */

#include "../../libs/i2cmaster/i2cmaster.h"

#include "myi2c.h"

void myi2c_init(void){
    i2c_init();

    i2c_start_wait(GYRO_ADDR + MYI2C_WRITE);

    //low speed ODR disabled
    i2c_write(LOW_ODR);
    i2c_write(0x00);

    //0x00 = 0b00000000
    //(+/- 245 degrees/second full scale)
    i2c_write(CTRL_REG4);
    i2c_write(0x00);

    //0x2A = 0b00101010
    //DR = 00 (100 Hz ODR); BW = 10 (25 Hz bandwidth); PD =1 (normal mode); Zen = 0, Xen = 1, Yen = 0
    i2c_write(CTRL_REG1);
    i2c_write(0x2a);

    i2c_stop();
}

int16_t myi2c_read_x_gyro(void){
    i2c_start_wait(GYRO_ADDR + MYI2C_WRITE);

    //request gyro x-axis and enable auto-increment
    i2c_write(GYRO_X_L | (1<<7));

    i2c_rep_start(GYRO_ADDR + MYI2C_READ);
    uint8_t gyro_x_l = i2c_readAck();
    uint8_t gyro_x_h = i2c_readNak();
    int16_t gyro_x = (gyro_x_h << 8) | (gyro_x_l);

    i2c_stop();

    return gyro_x;

}
