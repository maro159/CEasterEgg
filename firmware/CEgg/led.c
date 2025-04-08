/*
 * led.c
 *
 * Created: 07.04.2025 17:28:47
 *  Author: mrcm7
 */ 

#include "pins.h"
#include "led.h"
#include "util/delay.h"

void init_led(void)
{
	// set pin direction to output
	PORTA.DIRSET = (1U << LED_EN_PIN) | (1U << DATA_PIN) | (1U << CLOCK_PIN);
	// invert logic
	PORTA.PINCTRL(LED_EN_PIN) |= PORT_INVEN_bm;
}

void led_shift_bit(bool state)
{
	if (state)
		PORTA.OUTSET = (1 << DATA_PIN);
	else
		PORTA.OUTCLR = (1 << DATA_PIN);
	
	// NOTE: 100 ns setup time is enough
	_delay_us(0.2);
	
	// clock
	PORTA.OUTSET = (1 << CLOCK_PIN);
	_delay_us(0.2);
	PORTA.OUTCLR = (1 << CLOCK_PIN);
}

void led_shift_byte(uint8_t data)
{
	// trick to have efficient mask shift
	for (uint8_t mask = 0x80; mask; mask >>= 1)
	{
		led_shift_bit(data & mask);
	}
}


void led_set(uint16_t pattern)
{
	// MSB first
	led_shift_byte((uint8_t)(pattern >> 8));
	led_shift_byte((uint8_t)(pattern));
}