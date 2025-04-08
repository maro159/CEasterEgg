/*
 * buzzer.c
 *
 * Created: 08.04.2025 00:26:05
 *  Author: mrcm7
 */ 

#include "pins.h"
#include "buzzer.h"

void init_buzzer(void)
{
	// set pin direction to output
	PORTA.DIRSET = (1U << BUZZER_PIN);
	// invert logic
	PORTA.PINCTRL(BUZZER_PIN) |= PORT_INVEN_bm;
}