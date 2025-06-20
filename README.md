# CH32V203C8T6 Pediatric Vein Finder

A specialized medical device designed specifically for children's healthcare

## Project Overview
This project implements a pediatric vein finder device using the CH32V203C8T6 RISC-V microcontroller. The device is specifically designed to help healthcare professionals locate veins in children, making medical procedures less stressful and more accurate for young patients.

**Designed by**: Prof. Pham Thi Thu Hien, ME. Nguyen Le Y, Student Vo Dang Khoa
**Institution**: International University VNU HCMC  
**Purpose**: Gift to Children's Hospital 1, Ho Chi Minh City  
**Target Users**: Pediatric healthcare professionals

## Hardware Components
- **Microcontroller**: CH32V203C8T6 (32-bit RISC-V architecture)
- **Proximity Sensor**: Analog sensor for automatic activation
- **Illumination System**: Multiple LEDs for vein visualization
- **Status LEDs**: Visual indicators for device operation
- **Control Interface**:
  - Left button (PB10) - Navigation/Settings
  - Right button (PB11) - Navigation/Settings  
  - Output button (PA9) - Manual scanner control
- **Power Management**: Efficient power control circuitry
- **Debug Interface**: USART1 for technical monitoring

## Features
- **Child-Friendly Design**: Specifically engineered for pediatric use with gentle illumination
- **Proximity Sensor**: Automatic activation when placed near the patient's skin
- **LED Indicators**: Visual feedback for system status and operation
- **Intuitive Controls**: Simple button interface suitable for clinical environments
  - Left/Right buttons for navigation and settings
  - Output button to manually control vein scanner LED
  - Simultaneous press of Left+Right buttons for safe power-off
- **Safety Features**: 
  - Auto-off functionality after 30 seconds to prevent overheating
  - Low-power design for extended battery life
  - Gentle near-infrared illumination safe for children
- **Clinical Feedback**: UART debug output for technical monitoring (115200 baud)

## Device Images

### Device Views
![Front Device View with LED](images/front%20%20device%20view%20with%20led%20.jpg)
*Front view of the vein finder device showing the LED illumination system*

![Back Device View](images/back%20device%20view.jpg)
*Back view of the device showing the control interface and connections*

### Clinical Testing
![Clinical Test](images/clincal%20test.jpg)
*Device being tested in clinical environment*

![Clinical Test 2](images/clinical%20test%202.jpg)
*Additional clinical testing demonstration*

## Clinical Benefits
- **Reduced Patient Stress**: Minimizes multiple needle attempts in children
- **Improved Accuracy**: Enhanced vein visibility for healthcare professionals
- **Time Efficient**: Faster vein location reduces procedure time
- **Safety First**: Designed with pediatric safety standards in mind
- **Portable**: Compact design suitable for various clinical settings

## System Operation
- **Startup Sequence**: LED test pattern confirms system functionality
- **Standby Mode**: Gentle LED chase animation indicates ready state
- **Proximity Detection**: Automatic activation when sensor detects nearby skin
- **Manual Override**: Output button provides manual control for healthcare professionals
- **Safety Shutdown**: Auto-off after 30 seconds or manual power-off via dual button press
- **Clinical Monitoring**: Real-time system status via debug interface

## Pediatric Considerations
This device has been specifically designed with children's healthcare in mind:
- **Gentle Illumination**: Optimized light intensity for comfort
- **Quick Operation**: Minimizes exposure time
- **Reliable Performance**: Consistent results to reduce repeat procedures
- **Safety First**: Multiple safety mechanisms to protect young patients

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

## Development Information
- **Developer**: Prof. Pham Thi Thu Hien, ME. Nguyen Le Y, Student Vo Dang Khoa, International University VNU HCMC
- **Development Platform**: MounRiver Studio IDE
- **Target Device**: CH32V203C8T6 (32-bit RISC-V microcontroller)
- **Programming Language**: C
- **Hardware Description**: Custom PCB design for pediatric applications

## Building and Flashing
This project is configured for MounRiver Studio IDE:
1. Open the project in MounRiver Studio
2. Configure the target device (CH32V203C8T6)
3. Build the project to generate .elf and .hex files
4. Use the integrated flash tool to program the microcontroller
5. Verify operation through the debug interface

## Technical Specifications
- **Operating Voltage**: 3.3V
- **Debug Interface**: USART1 (115200 baud, 8N1)
- **Proximity Sensor**: Analog input with configurable threshold
- **Safety Timer**: 30-second auto-off functionality
- **Power Consumption**: Optimized for battery operation

## Dedication
This project is dedicated to improving pediatric healthcare at Children's Hospital 1, Ho Chi Minh City. The device represents a commitment to making medical procedures more comfortable and effective for young patients and their families.

---
*Developed with care for children's healthcare by Nguyen Le Y, International University VNU HCMC*

