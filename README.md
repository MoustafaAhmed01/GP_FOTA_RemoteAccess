# FOTA and Vehicle Remote Access Graduation Project

## Overview
My graduation project focused on Firmware Over-The-Air (FOTA) updates and Vehicle Remote Access, supervised by Dr. Mohamed Reyad and sponsored by Valeo. The hardware support for the project was provided by Valeo, and our mentor was Eng. Ehab Shalaan. The project incorporated cloud services, a mobile application, a website, and three custom PCBs.

## Project Components
### 1. Cloud Infrastructure
- **Firebase**: Used for real-time database and authentication.
- **MQTT**: Employed for message queuing and telemetry transport.

### 2. Mobile Application
Developed to interact with the vehicle's systems, providing notifications and controls for firmware updates and vehicle functionalities.

### 3. Website
A companion website for monitoring and managing vehicle updates and statuses.

### 4. Custom PCBs
#### PCB 1: FOTA Master
- **Components**: 
  - STM32F103C8T6 (ARM MCU, Blue Pill)
  - ESP8266 (NodeMCU)
  - CAN Transceiver
  - LCD Display
  - Keypad
- **Functionality**: 
  - Acts as the central controller for updating other Electronic Control Units (ECUs) in the vehicle.
  - Monitors MQTT topics for new firmware updates.
  - Downloads new firmware upon confirmation from the mobile app.
  - Displays download progress on both the LCD and the mobile app.
  - Transfers the firmware to the target MCU via UART.

#### PCB 2: Target ECU
- **Components**:
  - A9G GSM/GPRS Module
  - STM32F103C8T6
  - CAN Transceiver
- **Functionality**:
  - Contains both bootloader and application code.
  - Receives new firmware updates from the FOTA Master.
  - Handles corner cases such as incomplete downloads or flash memory states.
  - Implements a watchdog timer to ensure reliability.
  - Application code interfaces with the A9G module for network connectivity and MQTT communication.
  - Controls vehicle functions such as engine start/stop, AC control, speed control, emergency control, door control, and vehicle location.

#### PCB 3: Peripheral Control
- **Components**:
  - Push Buttons
  - Motors
  - LEDs
  - Fan (acting as AC)
  - Servo Motor
- **Functionality**:
  - Provides manual control for vehicle functions.
  - Sends status updates to the Target ECU, which relays them to the mobile app.
  - Receives commands from the mobile app to control various vehicle functions and acknowledges the commands.

## How It Works
1. **Firmware Update Process**:
   - The OEM uploads a new firmware to the cloud.
   - The mobile app receives a notification via MQTT.
   - Upon user confirmation, the FOTA Master downloads the firmware.
   - The download progress is displayed on the LCD and the mobile app.
   - The firmware is transferred to the Target ECU, which processes and installs it.

2. **Vehicle Remote Access**:
   - The Target ECU, via the A9G module, ensures continuous network connectivity.
   - The mobile app can control various vehicle functions and receive status updates.
   - The Peripheral Control PCB manages manual overrides and status feedback to the mobile app.

## Conclusion
This project demonstrates the integration of cloud services, mobile applications, and embedded systems to provide reliable FOTA updates and remote vehicle access. It showcases the potential for modernizing vehicle maintenance and control, ensuring both efficiency and user convenience.
