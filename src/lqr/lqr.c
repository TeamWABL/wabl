/**
 * WABL Linear Quadratic Regulator
 * @file    lqr.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:30
 * @edited  2015-04-28 14:39:59
 */

// lqr weighting constants {x, x_dot, phi, phi_dot}
float K[4] = {-10.4113, -2.5702, -0.8970, -1.5861};

float lqr_update(float positionRef, float position, float velocity, float angle, float a_velocity){
    float w_position = position * K[0];
    float w_velocity = velocity * K[1];
    float w_angle = angle * K[2];
    float w_a_velocity = a_velocity * K[3];
    
    float torqueRef = positionRef - w_position - w_velocity - w_angle - w_a_velocity;
    return torqueRef;
}
