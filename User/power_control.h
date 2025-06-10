/********************************** (C) COPYRIGHT *******************************
 * File Name          : power_control.h
 * Description        : Power control functions
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __POWER_CONTROL_H
#define __POWER_CONTROL_H

#include "debug.h"

/* System enable pin definition */
#define SYS_EN_PORT GPIOA
#define SYS_EN_PIN GPIO_Pin_10

/* Function prototypes */
void power_control_init(void);
void system_on(void);
void system_off(void);

#endif /* __POWER_CONTROL_H */
