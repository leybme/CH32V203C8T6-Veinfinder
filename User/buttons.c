/********************************** (C) COPYRIGHT *******************************
 * File Name          : buttons.c
 * Description        : Button input control functions implementation
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "buttons.h"

/*********************************************************************
 * @fn      buttons_init
 *
 * @brief   Initialize button GPIO pins.
 *
 * @return  none
 */
void buttons_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // Enable GPIOB and GPIOA clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);
    
    // Configure BTN_L (PB10) and BTN_R (PB11) as input with pull-up resistors
    GPIO_InitStructure.GPIO_Pin = BTN_L_PIN | BTN_R_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // Input with pull-up
    GPIO_Init(BTN_L_PORT, &GPIO_InitStructure);
    
    // Configure BTN_OUT (PA9) as input with pull-up resistor
    GPIO_InitStructure.GPIO_Pin = BTN_OUT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // Input with pull-up
    GPIO_Init(BTN_OUT_PORT, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      read_btn_left
 *
 * @brief   Read the state of the left button (PB10).
 *
 * @return  0: Button is pressed, 1: Button is released
 */
uint8_t read_btn_left(void) {
    return GPIO_ReadInputDataBit(BTN_L_PORT, BTN_L_PIN);
}

/*********************************************************************
 * @fn      read_btn_right
 *
 * @brief   Read the state of the right button (PB11).
 *
 * @return  0: Button is pressed, 1: Button is released
 */
uint8_t read_btn_right(void) {
    return GPIO_ReadInputDataBit(BTN_R_PORT, BTN_R_PIN);
}

/*********************************************************************
 * @fn      read_btn_output
 *
 * @brief   Read the state of the output button (PA9).
 *
 * @return  0: Button is pressed, 1: Button is released
 */
uint8_t read_btn_output(void) {
    return GPIO_ReadInputDataBit(BTN_OUT_PORT, BTN_OUT_PIN);
}
