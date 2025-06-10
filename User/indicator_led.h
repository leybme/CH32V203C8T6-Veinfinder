/********************************** (C) COPYRIGHT *******************************
 * File Name          : indicator_led.h
 * Description        : LED indicator control functions
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __INDICATOR_LED_H
#define __INDICATOR_LED_H

#include "debug.h"

/* LED pin definitions */
#define LED_PORT GPIOB
#define LED_PIN_1 GPIO_Pin_3
#define LED_PIN_2 GPIO_Pin_4
#define LED_PIN_3 GPIO_Pin_5
#define LED_PIN_4 GPIO_Pin_6
#define LED_PIN_5 GPIO_Pin_7
#define LED_PINS (LED_PIN_1 | LED_PIN_2 | LED_PIN_3 | LED_PIN_4 | LED_PIN_5)
#define BLINK_DELAY_MS 500  // LED blink delay in milliseconds
#define CHASE_DELAY_MS 10  // LED chase delay in milliseconds

/* Function prototypes */
void led_init(void);
void toggle_leds(void);
void led_on(uint16_t led_pin);
void led_off(uint16_t led_pin);
void all_leds_off(void);
void all_leds_on(void);
void chase_leds(void);

#endif /* __INDICATOR_LED_H */
