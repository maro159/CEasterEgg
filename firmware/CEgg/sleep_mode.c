/*
 * sleep_mode.c
 *
 * Created: 07.04.2025 20:28:49
 *  Author: mrcm7
 */ 

#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "pins.h"
#include "sleep_mode.h"
#include "led.h"

void init_sleep(void)
{
	// sleep mode - Power-Down
	//SLPCTRL.CTRLA |= (SLPCTRL_SMODE_PDOWN_gc | SLPCTRL_SEN_bm);
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void sleep_mode_on(void)
{
	led_disable();	
	sleep_enable();	// unlock ability to sleep
	uint8_t tmp = RTC.PITCTRLA;	// save PIT control register
	RTC.PITCTRLA &= ~RTC_PITEN_bm; // prevent PIT from waking up CPU
	sei();	// enable global interrupts to be able to wake up
	sleep_cpu(); // actual sleep
	// ** CPU will wake here on interrupt **
	RTC.PITCTRLA = tmp; // restore save PIT control register
	sleep_disable();
	led_enable();
}

