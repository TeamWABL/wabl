/**
 * 
 * @file    sound.c
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-05-10 19:45:57
 * @edited  2015-05-10 20:29:40
 */

#include <pololu/orangutan.h>
#include <avr/pgmspace.h>

#include "sound.h"

//unsigned char critical_battery[3] = {C(1), B(1), A(1)};

const char critical_battery[] PROGMEM = "! CO3 BO3 AO3";

void sound_play_melody(melody_e melody){
    switch (melody){
        case BATTERY_CRITICAL:
            play_from_program_space(critical_battery);
            break;
        case BATTERY_LOW:
            //do stuff
            break;
        default:
            break;
    }
} 
