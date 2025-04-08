/*
 * pins.h
 *
 * Created: 07.04.2025 11:04:26
 *  Author: mrcm7
 */ 


#ifndef PINS_H_
#define PINS_H_

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdbool.h>

// pin definitions
#define BUTTON_PIN 7
#define LED_EN_PIN 6
#define BUZZER_PIN 2

#define CLOCK_PIN 3
#define DATA_PIN 1

// macro to replace PINnCTRL
#define PINCTRL_HELPER(n) PIN##n##CTRL
#define PINCTRL(n) PINCTRL_HELPER(n)

// input checks
//#define IS_BUTTON (bit_is_clear(PORTA.IN, BUTTON_PIN)) // active low: 0 = pressed

#endif /* PINS_H_ */