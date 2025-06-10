/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *USART Print debugging routine:
 *USART1_Tx(PA9).
 *This example demonstrates using USART1(PA9) as a print debug port output.
 *
 */

#include "debug.h"
#include "indicator_led.h"
#include "buttons.h"
#include "power_control.h"
#include "vein_scanner.h"

/* Global typedef */

/* Global defines */
#define LONG_PRESS_THRESHOLD 1000 // 1000 * 50ms = 5 seconds for long press

/* Function prototypes */
void system_init(void);
void check_button_long_press(void);

/* Global Variable */
static uint32_t btn_output_press_duration = 0; // Counter for button long press

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{ // Initialize system components
    system_init();
    power_control_init(); // Initialize SYS_EN pin and turn system on
    led_init();
    buttons_init();
    vein_scanner_init();

    printf("=== Running LED tests at startup ===\r\n");

    all_leds_on();
    Delay_Ms(500); // 1 second delay
    all_leds_off();

    // vein_test();
    while (1)
    {
        printf("Buttons initialized. BTN_L=PB10, BTN_R=PB11, BTN_OUT=PA9\r\n");
        // Main application loop    while (1) {    // Read button states
        uint8_t btn_left = read_btn_left();
        uint8_t btn_right = read_btn_right();
        uint8_t btn_output = read_btn_output();

        // Check if both left and right buttons are pressed simultaneously - turn off system
        if (btn_left == 0 && btn_right == 0)
        {
            // Both left and right buttons pressed - turn off system
            led_on(LED_PIN_1);
            led_on(LED_PIN_5);
            printf("Left and right buttons pressed simultaneously - Shutting down system\r\n");
            system_off(); // Turn off system
        }
        else if (btn_left == 0)
        {
            // Left button pressed - just turn on indicator LED
            led_on(LED_PIN_1);
            printf("Left button pressed\r\n");
        }
        else if (btn_right == 0)
        {
            // Right button pressed - just turn on indicator LED
            led_on(LED_PIN_5);
            printf("Right button pressed\r\n");
        }

        // Check for output button press (controls vein scanner LED and system power)
        if (btn_output == 0)
        {
            // Output button pressed, turn on LED 3
            led_on(LED_PIN_3);

            // Count duration for long press detection
            btn_output_press_duration++;
            vein_on();

            // Reset press duration counter when button is released
            btn_output_press_duration = 0;
        }

        // Update vein scanner timer (for auto-off after 30 seconds)
        vein_timer_update();

        // If no button is pressed, run the normal LED chase
        if (btn_left != 0 && btn_right != 0 && btn_output != 0)
        {
            chase_leds();
        }

        // Delay to avoid flooding the console
        Delay_Ms(50);
    }
}

/*********************************************************************
 * @fn      system_init
 *
 * @brief   Initialize system components.
 *
 * @return  none
 */
void system_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();

    // Initialize UART for debug output
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    printf("System initialized\r\n");
}
