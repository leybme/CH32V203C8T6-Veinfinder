/********************************** (C) COPYRIGHT *******************************
 * File Name          : vein_scanner.c
 * Description        : Vein scanner LED control functions implementation
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "vein_scanner.h"
#include "debug.h"
#include "power_control.h"

/* Variables */
uint32_t start_vein_counter = 0;              // Counter for LED on duration
const uint32_t VEIN_AUTO_OFF_COUNETER = 6000; // // 6000 * 1ms = 30 seconds for auto-off
uint8_t led_state = LED_OFF;                  // Current LED state (on/off)

/*********************************************************************
 * @fn      vein_scanner_init
 *
 * @brief   Initialize the vein scanner LED output (PA4) with direct GPIO.
 *
 * @return  none
 */
void vein_scanner_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable GPIOA and AFIO clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // Make sure there's no remapping affecting PA4
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, DISABLE);

    // Configure PA4 as digital output
    GPIO_InitStructure.GPIO_Pin = VEIN_OUT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VEIN_OUT_PORT, &GPIO_InitStructure);

    // Force reset the pin first to ensure a clean state
    GPIOA->BCR = VEIN_OUT_PIN;
    // Set initial state to off
    led_state = LED_OFF;

    // Turn off the vein scanner LED initially
    GPIO_ResetBits(VEIN_OUT_PORT, VEIN_OUT_PIN);

    printf("Vein scanner LED initialized with simple on/off control (PA4)\r\n");

    // Debug: Check if pin is properly configured
    uint8_t port_config = (GPIOA->CFGLR >> (4 * 4)) & 0xF; // Get configuration for PA4
    printf("Debug - PA4 configuration: 0x%02X (should be 0x03 for output push-pull)\r\n", port_config);

    // Test toggle to verify hardware
    printf("Performing LED test...\r\n");
    GPIO_SetBits(VEIN_OUT_PORT, VEIN_OUT_PIN);   // Turn on
    Delay_Ms(100);                               // 500ms delay
    GPIO_ResetBits(VEIN_OUT_PORT, VEIN_OUT_PIN); // Turn off    printf("LED test complete. Did you see the LED flash?\r\n");
}

/*********************************************************************
 * @fn      vein_on
 *
 * @brief   Turn on the vein scanner LED and start auto-off timer
 *
 * @return  none
 */
void vein_on(void)
{
    if (led_state == LED_ON)
    {
        printf("Vein scanner LED is already ON\r\n");
        return; // Already on, no action needed
    }
    start_vein_counter = counterTimer;
    // Turn on LED - explicit set PA4 high
    GPIO_SetBits(VEIN_OUT_PORT, VEIN_OUT_PIN);
    led_state = LED_ON;
    // Debug output
    printf("Vein scanner LED turned ON (PA%d, pin %d) for 30 seconds\r\n",
           (VEIN_OUT_PORT == GPIOA) ? 'A' - 'A' : ((VEIN_OUT_PORT == GPIOB) ? 'B' - 'A' : ((VEIN_OUT_PORT == GPIOC) ? 'C' - 'A' : 'D' - 'A')),
           __builtin_ctz(VEIN_OUT_PIN));
}

/*********************************************************************
 * @fn      vein_off
 *
 * @brief   Turn off the vein scanner LED.
 *
 * @return  none
 */
void vein_off(void)
{
    if (led_state == LED_OFF)
    {
        printf("Vein scanner LED is already OFF\r\n");
        return; // Already off, no action needed
    }
    // Turn off LED - explicit reset PA4 low
    GPIO_ResetBits(VEIN_OUT_PORT, VEIN_OUT_PIN);
    led_state = LED_OFF;

    // Debug output
    printf("Vein scanner LED turned OFF (PA%d, pin %d)\r\n",
           (VEIN_OUT_PORT == GPIOA) ? 'A' - 'A' : ((VEIN_OUT_PORT == GPIOB) ? 'B' - 'A' : ((VEIN_OUT_PORT == GPIOC) ? 'C' - 'A' : 'D' - 'A')),
           __builtin_ctz(VEIN_OUT_PIN));
}

/*********************************************************************
 * @fn      vein_toggle
 *
 * @brief   Toggle the vein scanner LED. If it's off, turn it on.
 *          If it's already on, turn it off.
 *
 * @return  none
 */
void vein_toggle(void)
{
    // Toggle LED state
    if (led_state == LED_ON)
    {
        vein_off();
    }
    else
    {
        vein_on();
    }
}
void f_vein_off(void)
{
    GPIO_ResetBits(VEIN_OUT_PORT, VEIN_OUT_PIN);
    led_state = LED_OFF;
}
void f_vein_on(void)
{
    GPIO_SetBits(VEIN_OUT_PORT, VEIN_OUT_PIN);
    led_state = LED_ON;
}

/*********************************************************************
 * @fn      vein_timer_update
 *
 * @brief   Check if auto-off time has been reached and turn off LED if needed.
 *          Call this function periodically from main loop.
 *
 * @return  none
 */
void vein_timer_update(void)
{
    // Check if LED is on and auto-off timer is set
    if (led_state == LED_ON && start_vein_counter > 0)
    {
        // Check if the auto-off time has been reached
        if ((counterTimer - start_vein_counter) >= VEIN_AUTO_OFF_COUNETER)
        {
            vein_off(); // Turn off LED after 30 seconds
            printf("Vein scanner LED auto-off after 30 seconds\r\n");
            start_vein_counter = 0; // Reset counter
        }
        power_timer_counter = 10000; // Reset power control timer
    }

}

// Preview and brightness control functions removed - using simple on/off control

/*********************************************************************
 * @fn      vein_test
 *
 * @brief   Direct test function for vein scanner LED - bypasses state tracking
 *
 * @return  none
 */
void vein_test(void)
{
    printf("=== VEIN LED TEST START ===\r\n");

    // Direct port manipulation for testing
    printf("Setting PA4 HIGH directly\r\n");
    GPIOA->BSHR = GPIO_Pin_4; // Set PA4 high
    Delay_Ms(1000);           // 1 second on

    printf("Setting PA4 LOW directly\r\n");
    GPIOA->BCR = GPIO_Pin_4; // Set PA4 low
    Delay_Ms(1000);          // 1 second off

    printf("Setting PA4 HIGH using GPIO_SetBits\r\n");
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    Delay_Ms(1000); // 1 second on

    printf("Setting PA4 LOW using GPIO_ResetBits\r\n");
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);

    printf("=== VEIN LED TEST COMPLETE ===\r\n");
}
