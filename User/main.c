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
#include "sensor.h"

/* Global typedef */

/* Global defines */
#define LONG_PRESS_THRESHOLD 1000 // 1000 * 50ms = 5 seconds for long press

/* Function prototypes */
void system_init(void);
void check_button_long_press(void);
void buttons_handle(void);
void proximity_sensor_handle(void);
void vein_handle_pwm(uint8_t duty_cycle);

int8_t vein_intensity = 1; // Global variable to track vein intensity (0-255)
/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    // Initialize system components

    system_init();
    Delay_Ms(500);        // Delay for system not power up immediately
    power_control_init(); // Initialize SYS_EN pin and turn system on
    led_init();           // Initialize indicator LEDs
    buttons_init();
    Sensor_Init(); // Initialize proximity sensor
    vein_scanner_init();
    printf("=== Running LED tests at startup ===\r\n");
    all_leds_on();
    Delay_Ms(500); // 1 second delay
    all_leds_off();

    // vein_test();
    while (1)
    {
        // vein_handle_pwm(vein_intensity);
        buttons_handle(); // Handle button presses
        // Update vein scanner timer (for auto-off after 30 seconds)
        vein_timer_update();
        chase_leds(); // Chase LEDs for visual effect
        proximity_sensor_handle();
        // Delay to avoid flooding the console
        Delay_Ms(1);
        counterTimer++; // Increment global counter for mimic millisecond timer
       power_timer_counter--; // Decrement power control timer

        // Check if power control timer has reached zero
        if (power_timer_counter == 0)
        {
            printf("Power control timer expired, turning off system...\r\n");
            system_off(); // Turn off system if timer expires
        }

    }
}
void buttons_handle()
{
uint32_t current_counter = counterTimer;    // Get current time from global counter
    static uint32_t last_handle_counter = 0;    // Last time buttons were handled

    static const uint16_t DELAY_COUNTER = 10;    // 100ms delay for button handling
    static const uint8_t VALID_PRESS_COUNT = 3; // 3 continuous triggers for valid press
    // Button press counters for validation
    static uint8_t btn_left_count = 0;
    static uint8_t btn_right_count = 0;
    static uint8_t btn_output_count = 0;

    if (current_counter - last_handle_counter > DELAY_COUNTER)
    {
        last_handle_counter = current_counter;
        // Handle button states
        uint8_t btn_left = read_btn_left();
        uint8_t btn_right = read_btn_right();
        uint8_t btn_output = read_btn_output();

        // Count continuous button presses
        {
            if (btn_left == 0)
            {
                btn_left_count++;
            }
            else
            {
                btn_left_count = 0;
            }

            if (btn_right == 0)
            {
                btn_right_count++;
            }
            else
            {
                btn_right_count = 0;
            }

            if (btn_output == 0)
            {
                btn_output_count++;
            }
            else
            {
                btn_output_count = 0;
            }
        }

        // Check for valid button presses (5 continuous triggers)
        if (btn_left_count >= VALID_PRESS_COUNT && btn_right_count >= VALID_PRESS_COUNT)
        {
            led_on(LED_PIN_1);
            led_on(LED_PIN_5);
            printf("Left and right buttons pressed simultaneously - Shutting down system\r\n");
            system_off(); // Turn off system
        }
        else if (btn_left_count >= VALID_PRESS_COUNT)
        {
            led_on(LED_PIN_1);
            printf("Left button pressed\r\n");
        }
        else if (btn_right_count >= VALID_PRESS_COUNT)
        {
            // Right button pressed - just turn on indicator LED
            led_on(LED_PIN_5);
            printf("Right button pressed\r\n");
        }

        // Check for output button press (controls vein scanner LED and system power)
        if (btn_output_count >= VALID_PRESS_COUNT)
        {
            // Output button pressed, turn on LED 3
            led_on(LED_PIN_3);
            vein_toggle(); // Toggle vein scanner LED state
            Delay_Ms(1000);
        }
    }
}
void proximity_sensor_handle(void)
{
    // Handle proximity sensor logic here
    // This function can be called periodically to check sensor state
    static const uint32_t PROXIMITY_CHECK_INTERVAL_COUNTER = 5; // Check every 5 iterations (5 * 5ms = 25ms)
    static const uint16_t PROXIMITY_THRESHOLD = 200;            // Threshold for proximity detection

    static uint8_t proximity_state_detected = 0; // 0 = off, 1 = on
    static uint32_t last_check_counter = 0;      // Last time proximity sensor was checked
    uint32_t current_counter = counterTimer;     // Get current time from global counter
    if (current_counter - last_check_counter > PROXIMITY_CHECK_INTERVAL_COUNTER)
    {
        last_check_counter = current_counter; // Update last check time
    }
    else
    {
        return; // Skip this iteration if not time to check
    }
    uint16_t current_proximity_value = Sensor_ReadAnalog(); // Read the current proximity sensor value
    proximity_state_detected = (current_proximity_value < PROXIMITY_THRESHOLD) ? 1 : 0;
    if(proximity_state_detected)
    {
        start_vein_counter = counterTimer; // Start the vein scanner timer when proximity is detected
    }



    if (proximity_state_detected != last_proximity_state_detected)
    {
        last_proximity_state_detected = proximity_state_detected;
        if (proximity_state_detected)
        {
            // Proximity detected, turn on vein scanner LED
            vein_on();
            printf("Proximity detected, turning on vein scanner LED\r\n");
        }
        else
        {
            // No proximity detected, turn off vein scanner LED
            vein_off();
            printf("No proximity detected, turning off vein scanner LED\r\n");
        }
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
void vein_handle_pwm(uint8_t duty_cycle)
{
    static uint8_t counter = 0;
    counter++;
    counter = counter % 10;
    if (counter >= duty_cycle)
    {
        f_vein_off(); // Turn off LED
    }
    else
    {
        f_vein_on(); // Turn on LED
    }
}
