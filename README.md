# CH32V203C8T6 Vein Finder

## Project Overview
This project implements a vein finder device using the CH32V203C8T6 microcontroller. It's designed to illuminate veins under the skin to assist with medical procedures.

## Hardware Components
- **Microcontroller**: CH32V203C8T6 (RISC-V architecture)
- **LEDs**: Multiple indicator LEDs for system status
- **Buttons**:
  - Left button (PB10)
  - Right button (PB11)
  - Output button (PA9)
- **Vein Scanner**: LED-based system to illuminate veins

## Features
- **LED Indicators**: Visual feedback for system status
- **Button Controls**: Interactive control of the device
  - Left/Right buttons for navigation
  - Output button to control vein scanner LED
  - Simultaneous press of Left+Right buttons to power off the system
- **Power Management**: Auto-off functionality and manual power control
- **UART Debug Output**: System status messages via USART1 (PA9)

## System Operation
- **Startup**: LED test sequence shows all LEDs turning on briefly
- **Normal Operation**: LED chase animation when no buttons are pressed
- **Vein Scanner**: Activates with output button and auto-turns off after 30 seconds
- **Power Control**: System can be turned off by pressing both left and right buttons simultaneously

## Project Structure
- **Core**: RISC-V core functionality
- **Debug**: Debug utilities
- **Peripheral**: CH32V203 peripheral drivers
- **Startup**: System initialization
- **User**: Application-specific code
  - `main.c`: Main program logic
  - `indicator_led.c/h`: LED control functions
  - `buttons.c/h`: Button interface
  - `power_control.c/h`: System power management
  - `vein_scanner.c/h`: Vein illumination functionality

## Building and Flashing
This project is configured for MounRiver Studio IDE. To build and flash:
1. Open the project in MounRiver Studio
2. Build the project to generate the .elf and .hex files
3. Use the built-in flash tool to program the CH32V203C8T6

## Serial Debug
Connect to the UART output (115200 baud) to view system status messages and debug information.

## License
Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
