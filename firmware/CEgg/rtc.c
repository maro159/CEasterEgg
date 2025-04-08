/*
 * rtc.c
 *
 * Created: 07.04.2025 19:08:11
 *  Author: mrcm7
 */ 


#include <avr/interrupt.h>
#include "pins.h"
#include "rtc.h"

#define TIMER_COUNT_500MS 51 // 50 * 10 ms + 1 to accommodate for pre-decrement in ISR
 
volatile uint8_t time_flags = 0x00;

void init_rtc(void)
{
	/*
	 * NOTE: The peripheral clock (CLK_PER) is required to be at least four times faster than the RTC clock (CLK_RTC)
	 * for reading the counter value, regardless of the prescaler setting
	 */
	
	// RTC general settings
	// 1.024 kHz clock	
	RTC.CLKSEL |= RTC_CLKSEL_INT1K_gc;
	
	// RTC interrupt each ~10ms
	while(RTC.STATUS & RTC_PERBUSY_bm);
	RTC.PER = 0x000A; // 10/1024Hz = 9.77 ms
	// enable interrupt on overflow
	RTC.INTCTRL |= RTC_OVF_bm;
	// enable module
	while(RTC.STATUS & RTC_CTRLABUSY_bm);
	RTC.CTRLA |= RTC_RTCEN_bm;
	
	// PIT interrupt each second
	while(RTC.PITSTATUS & RTC_CTRLBUSY_bm);
	RTC.PITCTRLA |= (RTC_PERIOD_CYC1024_gc | RTC_PITEN_bm);
}

ISR(RTC_CNT_vect)
{
	static uint8_t timer_count_500ms = TIMER_COUNT_500MS; // static to preserve value

	time_flags |= TIME_FLAG_10MS_bm;		// set 10ms flag
	
	if(--timer_count_500ms == 0)		// pre-decrement is faster
	{
		time_flags |= TIME_FLAG_500MS_bm;	// set 500ms flag
		timer_count_500ms = TIMER_COUNT_500MS;	// reset counter
	}
	RTC.INTFLAGS |= RTC_OVF_bm;	// clear interrupt flag
	return;
}


ISR(RTC_PIT_vect)
{
	RTC.PITINTFLAGS |= RTC_PI_bm; 
}