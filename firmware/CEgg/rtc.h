/*
 * rtc.h
 *
 * Created: 07.04.2025 19:08:02
 *  Author: mrcm7
 */ 


#ifndef RTC_H_
#define RTC_H_

#define TIME_FLAG_10MS_bm 0x01
#define TIME_FLAG_500MS_bm 0x02

extern volatile uint8_t time_flags;

void init_rtc(void);

#endif /* RTC_H_ */