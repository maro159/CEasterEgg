/*
 * button.h
 *
 * Created: 11.04.2024 00:57:40
 *  Author: mrcm7
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "pins.h"

void init_button(void);
static inline bool button_clicked(void) { return bit_is_clear(PORTA.IN, BUTTON_PIN); } // active low: 0 = pressed

#endif /* BUTTON_H_ */