/********************************** (C) COPYRIGHT *******************************
 * File Name          : vein_scanner.h
 * Description        : Vein scanner LED control functions
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __VEIN_SCANNER_H
#define __VEIN_SCANNER_H

#include "debug.h"
#include "ch32v20x_gpio.h"
#include "ch32v20x_tim.h"
#include "ch32v20x_rcc.h"

/* Vein scanner LED output pin definition */
#define VEIN_OUT_PORT GPIOA
#define VEIN_OUT_PIN GPIO_Pin_4

/* Simple LED control definitions */
#define LED_ON  1
#define LED_OFF 0

/* External variables */
extern uint32_t auto_off_timer;    // Timer for auto-off functionality
extern uint8_t led_state;          // Current LED state (on/off)

/* Function prototypes */
void vein_scanner_init(void);
void vein_on(void);   // Turn on LED
void vein_off(void);  // Turn off LED
void vein_toggle(void); // Toggle LED state
void vein_timer_update(void); // Update timer for auto-off functionality
void vein_test(void); // Test function to directly toggle vein LED

#endif /* __VEIN_SCANNER_H */
