# Bluetooth-Controlled Car Project - Lamborghini Aventador

## Overview

This project is a Bluetooth-controlled RC car modeled after the Lamborghini Aventador. It utilizes an Arduino-based system to control the car's movement via Bluetooth using a remote device (e.g., smartphone). The car can move forward, backward, turn left, right, and stop. The project has been maintained since 2021 and includes multiple iterations and improvements over time.

## Images

## Demo Videos

## Features

- **Bluetooth Control**: The car is controlled via a Bluetooth-enabled device.
- **Variable Speed Control**: Speed can be controlled based on the input received from the remote.
- **Remote Lock Mechanism**: An additional safety feature that locks the remote control.
- **Headlights**: The car has controllable front headlights.
- **Servo Steering**: The car is equipped with a servo motor to handle steering angles.
- **Battery Monitoring**: The car monitors battery status to indicate low battery levels.

## Code Structure

The project includes two primary code files:
1. **Car Control Code (`Lambourghini_Aventador.ino`)**: Manages the car's motor, steering, and Bluetooth communication.
2. **Remote Control Code (`Ghini_remote.ino`)**: Sends commands to the car via Bluetooth to control its movements and features.

### Car Code (`Lambourghini_Aventador.ino`)

- **Libraries Used**: 
  - `Servo.h` library to control the steering.
  
- **Variables**:
  - `int speed`, `int battery`, `int flght` for managing car speed, battery status, and lights.
  - `int right`, `int left`, `int rangle`, `int langle` to handle steering angles.
  
- **Key Functions**:
  - **Bluetooth Connection (`Serial.read()`)**: The car receives commands via serial communication from the Bluetooth module.
  - **Motor Control**: Controls the car's forward and backward movement based on the commands received.
  - **Servo Control**: Manages the steering of the car using the servo motor.
  - **Headlight Control**: The headlights can be toggled on/off using the Bluetooth remote.
  
### Remote Code (`Ghini_remote.ino`)

- **Bluetooth Commands**:
  - The remote sends specific commands (e.g., 'F', 'B', 'L', 'R') for controlling the car’s direction.
  
- **Key Features**:
  - **Motor Control Commands**: The remote can send commands to move forward (`F`), backward (`B`), and turn left (`L`) or right (`R`).
  - **Park Mode**: Enables/disables park mode for additional control.
  - **Headlight Toggle**: Turns the headlights on or off.

## Hardware Requirements

- **Arduino** (e.g., Arduino Uno)
- **Servo Motor** (for steering)
- **DC Motors** (for driving the car)
- **Bluetooth Module** (e.g., HC-05)
- **L298N Motor Driver**
- **LEDs for Headlights** (optional)
- **Battery and Power Supply**

## Getting Started

### 1. Uploading the Code
- Upload the car control code to the Arduino on the car.
- Upload the remote control code to the Arduino or any microcontroller handling the remote commands (or run the corresponding Bluetooth app).

### 2. Wiring
Ensure all components are connected correctly:
- **Servo Motor**: Connect to the Arduino's PWM pins for steering control.
- **DC Motors**: Connect to the motor driver and Arduino for movement.
- **Bluetooth Module**: Connect to Arduino RX and TX pins for communication.
  
### 3. Operating the Car
- Connect to the car’s Bluetooth module using your smartphone or another Bluetooth-enabled device.
- Use the remote control commands (forward, backward, left, right) to control the car’s movement.

## Versions

This repository includes multiple versions of the project. The code has evolved from basic movement functionality to more advanced features like remote locking and headlight control.

## Future Improvements

- Integrate a smartphone app for better control and UI.
- Add obstacle detection using ultrasonic sensors.
- Enhance battery monitoring with visual indicators.


## License

This project is open-source and available under the MIT License.
