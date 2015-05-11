/**
 * WABL Linear Quadratic Regulator
 * @file    lqr.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:30
 * @edited  2015-05-10 22:43:28
 */

// lqr weighting constants
double k_phi = -7.0940;
double k_phi_dot = -2.5901;
double k_x = -0.9100;
double k_x_dot = -1.8841;

double lqr(double positionRef_mm, double position_mm, double velocity_mm_s, double angle_mrad, double a_velocity_mrad_s){

    //calculate weighted values
    double w_position = position_mm * k_x;
    double w_velocity = velocity_mm_s * k_x_dot;
    double w_angle = angle_mrad * k_phi;
    double w_a_velocity = a_velocity_mrad_s * k_phi_dot;
    
    //combine values
    double torqueRef = (positionRef_mm - w_position - w_velocity - w_angle - w_a_velocity) / 1000;
    return torqueRef;
}
