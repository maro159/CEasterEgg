/*
 * buzzer.h
 *
 * Created: 08.04.2025 00:26:15
 *  Author: mrcm7
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

void init_buzzer(void);

static inline void buzzer_set() { PORTA.OUTSET = 1U << BUZZER_PIN; }
static inline void buzzer_reset() { PORTA.OUTCLR = 1U << BUZZER_PIN; }

#endif /* BUZZER_H_ */