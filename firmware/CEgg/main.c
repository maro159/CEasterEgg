/*
 * CEgg.c
 *
 * Created: 07.04.2025 10:34:16
 * Author : mrcm7
 */ 

#ifndef F_CPU
#warning	"F_CPU not defined. Define it in project properties."

#elif F_CPU != 20000000
#warning	"Wrong F_CPU frequency!"
#endif


#include <avr/io.h>
#include <util/delay.h>

#include "pins.h"
#include "rtc.h"
#include "led.h"
#include "button.h"
#include "buzzer.h"
#include "sleep_mode.h"

static void init_clock(void)
{
	// Unlock protected I/O registers
	CPU_CCP = CCP_IOREG_gc;
	// 16/20 MHz main clock
	CLKCTRL.MCLKCTRLA = CLKCTRL_CLKSEL_OSC20M_gc;
	// default prescaler for PER_CLK -> divide by 6
	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKCTRLB |= (CLKCTRL_PDIV_6X_gc | CLKCTRL_PEN_bm);
	// lock clock settings till next hardware reset
	CPU_CCP = CCP_IOREG_gc;
	CLKCTRL.MCLKLOCK = CLKCTRL_LOCKEN_bm;
}

static void init(void)
{
	init_clock();
	init_rtc();
	init_led();
	init_button();
}

static void on_click(void)
{
	static uint8_t click_count = 0;
	click_count++;
	
	if(click_count < 16)
	{
		/* NOTE: trick to use one variable for both:
		 * - led state to be shifted into register
		 * - count of clicks
		 */
		led_shift_bit(click_count & 0x01);
	}
	else
	{
		led_set(0x0000);
		click_count = 0;
	}
}

static void on_hold(void)
{
	sleep_mode_on();
}

int main(void)
{
	init();
	led_enable();
	
	buzzer_set();
	led_set(0xAAAA);
	_delay_ms(100);
	buzzer_reset();
	_delay_ms(900);
	
	buzzer_set();
	led_set(0x5555);
	_delay_ms(100);
	buzzer_reset();
	_delay_ms(900);
	led_set(0x0000);
		
	uint8_t button_states_10ms = 0;
	uint8_t button_states_500ms = 0;

	while (true)
	{
			if(time_flags & TIME_FLAG_10MS_bm)
			{
				// left shift button states 
				button_states_10ms <<= 1;
				// add current button state
				if(button_clicked())
				{
					button_states_10ms |= 0x01;		
					buzzer_set();
				}
				else
				{
					// no need to set LSB to 0 - it is done by operator <<
					buzzer_reset();					
				}
				// detect hold for 40ms to debounce
				if(0b00001111 == button_states_10ms)
				{
					on_click();
				}
				// reset time flag
				time_flags &= ~TIME_FLAG_10MS_bm;
			}
			
			if(time_flags & TIME_FLAG_500MS_bm)
			{
				// left shift button states
				button_states_500ms <<= 1;
				// add current button state
				if(button_clicked())
				{
					button_states_500ms |= 0x01;
				}
								
				// power off when button hold for at least 2000ms
				if(0b00001111 == button_states_500ms)
				{
					on_hold();
				}
				time_flags &= ~TIME_FLAG_500MS_bm;
			}
	}

	return 0;
}

