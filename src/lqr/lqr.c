/*
 * WABL Linear Quadratic Regulator
 * @file    lqr.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-04-28 14:23:30
 * @edited  2016-05- 3 23:27:38
 */

// lqr weighting constants
double k_phi = -4.3791;
double k_phi_dot = -2.5055;
double k_x = -0.4296;
double k_x_dot = -1.0200;
//  double k_x = 0.6436;
//  double k_x_dot = 0.7787;
//  double k_phi = -5.0436;
//  double k_phi_dot = -0.6328;

double lqr(double positionRef_mm, double position_mm, double velocity_mm_s, double angle_mrad, double a_velocity_mrad_s){

    //calculate weighted values
    double w_position = position_mm * k_x;
    double w_velocity = velocity_mm_s * k_x_dot;
    double w_angle = angle_mrad * k_phi;
    double w_a_velocity = a_velocity_mrad_s * k_phi_dot;
    
    //combine values
    double torqueRef = (positionRef_mm - w_position - w_velocity - w_angle - w_a_velocity) / 1000;
    torqueRef = (torqueRef > 5) ? 5 : torqueRef;
    torqueRef = (torqueRef < -5) ? -5 : torqueRef;
    return torqueRef;
}

void lqr_set_k_phi(double new_k_phi){
    k_phi = new_k_phi;
}

void lqr_set_k_phi_dot(double new_k_phi_dot){
    k_phi_dot = new_k_phi_dot;
}

void lqr_set_k_x(double new_k_x){
    k_x = new_k_x;
}

void lqr_set_k_x_dot(double new_k_x_dot){
    k_x_dot = new_k_x_dot;
}
