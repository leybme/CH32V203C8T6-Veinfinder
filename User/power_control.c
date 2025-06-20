/********************************** (C) COPYRIGHT *******************************
 * File Name          : power_control.c
 * Description        : Power control functions implementation
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "power_control.h"

/*********************************************************************
 * @fn      power_control_init
 *
 * @brief   Initialize the power control GPIO pin.
 *
 * @return  none
 */
uint32_t power_timer_counter = 10000; // Counter for power control timer


void power_control_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable GPIOA clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // Configure SYS_EN (PA10) as output push-pull
    GPIO_InitStructure.GPIO_Pin = SYS_EN_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(SYS_EN_PORT, &GPIO_InitStructure);

    // Keep the system on by default
    system_on();
}

/*********************************************************************
 * @fn      system_on
 *
 * @brief   Turn on the system by setting SYS_EN pin high.
 *
 * @return  none
 */
void system_on(void)
{
    // Set SYS_EN pin high to keep the system on
    GPIO_WriteBit(SYS_EN_PORT, SYS_EN_PIN, Bit_SET);
    printf("System power enabled (SYS_EN high)\r\n");
}

/*********************************************************************
 * @fn      system_off
 *
 * @brief   Turn off the system by setting SYS_EN pin low.
 *
 * @return  none
 */
void system_off(void)
{
    printf("System shutting down (SYS_EN low)...\r\n");
    // Set SYS_EN pin low to turn off the system
    GPIO_WriteBit(SYS_EN_PORT, SYS_EN_PIN, Bit_RESET);
    Delay_Ms(5000);
}
