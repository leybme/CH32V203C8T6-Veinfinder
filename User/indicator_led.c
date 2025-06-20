/********************************** (C) COPYRIGHT *******************************
 * File Name          : indicator_led.c
 * Description        : LED indicator control functions implementation
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "indicator_led.h"
#include "debug.h"

/*********************************************************************
 * @fn      led_init
 *
 * @brief   Initialize LED GPIO pins.
 *
 * @return  none
 */
void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable GPIOB clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // Configure LED pins
    GPIO_InitStructure.GPIO_Pin = LED_PINS;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);

    // Initially turn off all LEDs
    GPIO_Write(LED_PORT, GPIO_ReadOutputData(LED_PORT) & ~LED_PINS);
}

/*********************************************************************
 * @fn      toggle_leds
 *
 * @brief   Toggle all LED pins.
 *
 * @return  none
 */
void toggle_leds(void)
{
    uint16_t current = GPIO_ReadOutputData(LED_PORT);
    uint16_t next = current ^ LED_PINS;
    GPIO_Write(LED_PORT, next);
}

/*********************************************************************
 * @fn      led_on
 *
 * @brief   Turn on the specified LED pin.
 *
 * @param   led_pin - LED pin to turn on
 *
 * @return  none
 */
void led_on(uint16_t led_pin)
{
    GPIO_WriteBit(LED_PORT, led_pin, Bit_SET);
}

/*********************************************************************
 * @fn      led_off
 *
 * @brief   Turn off the specified LED pin.
 *
 * @param   led_pin - LED pin to turn off
 *
 * @return  none
 */
void led_off(uint16_t led_pin)
{
    GPIO_WriteBit(LED_PORT, led_pin, Bit_RESET);
}

/*********************************************************************
 * @fn      all_leds_off
 *
 * @brief   Turn off all LED pins.
 *
 * @return  none
 */
void all_leds_off(void)
{
    GPIO_Write(LED_PORT, GPIO_ReadOutputData(LED_PORT) & ~LED_PINS);
}

/*********************************************************************
 * @fn      all_leds_on
 *
 * @brief   Turn on all LED pins.
 *
 * @return  none
 */
void all_leds_on(void)
{
    GPIO_Write(LED_PORT, GPIO_ReadOutputData(LED_PORT) | LED_PINS);
}

/*********************************************************************
 * @fn      chase_leds
 *
 * @brief   Chase effect for LEDs: turn on LEDs one by one in sequence.
 *          The order is reversed: LED5 to LED1.
 *
 * @return  none
 */
void chase_leds(void)
{
    static uint16_t delay_counter = 0; // Counter for delay
    delay_counter++;
    if (delay_counter < 100)
    {
        return; // Delay for 100 iterations before changing state
    }
    delay_counter = 0; // Reset delay counter
    uint16_t led_pins[5] = {LED_PIN_5, LED_PIN_4, LED_PIN_3, LED_PIN_2, LED_PIN_1};
    static uint8_t counter = 0;
    counter++;                   // Increment counter to change LED state
    counter = counter % 10;      // Cycle through 0-9 for 5 LEDs (0-4 for on/off state)
    uint8_t state = counter % 2; // 0 or 1 for on/off state
    if (state == 1)
    {
        led_off(led_pins[counter / 2]);
    }
    else
    {

        led_on(led_pins[counter / 2]);
    }
}
