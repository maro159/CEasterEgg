/*
 * led.h
 *
 * Created: 07.04.2025 17:28:56
 *  Author: mrcm7
 */ 


#ifndef LED_H_
#define LED_H_

void init_led(void);
void led_set(uint16_t pattern);
void led_shift_bit(bool state);
void led_shift_byte(uint8_t data);

static inline void led_enable(void) { PORTA.OUTSET = 1U << LED_EN_PIN; }
static inline void led_disable(void) { PORTA.OUTCLR = 1U << LED_EN_PIN; }

#endif /* LED_H_ */