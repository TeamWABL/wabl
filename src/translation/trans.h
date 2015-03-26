/**
 * Module for translational position and velocity tracking
 * @file    trans.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-24 11:00:44
 * @edited  2015-03-25 23:03:41
 */

#ifndef TRANS_H
#define TRANS_H

void trans_init(void);

void trans_resetX(void);

float trans_getX(void);

float trans_getXDot(void);


#endif //ENCODER_H
