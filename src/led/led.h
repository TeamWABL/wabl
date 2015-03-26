/**
 *
 * @file    led.h
 * @author  Stephen Papierski <stephenpapierski@gmail.com>
 * @date    2015-03-25 22:39:03
 * @edited  2015-03-25 23:00:34
 */

#ifndef LED_H
#define LED_H

#include <avr/io.h>

#define LED_HB_DDR  DDRB
#define LED_HB_PORT PORTB
#define LED_HB_PIN  PINB
#define LED_HB_NUM  (1<<PORTB5)

void led_hb_init(void);
void led_hb(void);

#endif //LED_H
