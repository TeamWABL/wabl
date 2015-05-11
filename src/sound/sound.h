/**
 *
 * @file    sound.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-05-10 19:45:59
 * @edited  2015-05-10 20:29:38
 */

#ifndef SOUND_H
#define SOUND_H

typedef enum melody_e { BATTERY_CRITICAL,
                        BATTERY_LOW
} melody_e;

void sound_play_melody(melody_e melody);

#endif //SOUND_H
