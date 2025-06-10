/********************************** (C) COPYRIGHT *******************************
 * File Name          : buttons.h
 * Description        : Button input control functions
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include "debug.h"

/* Button pin definitions */
#define BTN_L_PORT GPIOB
#define BTN_L_PIN GPIO_Pin_10

#define BTN_R_PORT GPIOB
#define BTN_R_PIN GPIO_Pin_11

#define BTN_OUT_PORT GPIOA
#define BTN_OUT_PIN GPIO_Pin_9

/* Function prototypes */
void buttons_init(void);
uint8_t read_btn_left(void);
uint8_t read_btn_right(void);
uint8_t read_btn_output(void);

#endif /* __BUTTONS_H */
