# Monitor Device

## Overview
This project contains the source code for the Monitor device used to monitor and calibrate soil moisture using sensors. It interfaces with a liquid crystal display (LCD) to show real-time sensor readings and calibration status. The device is built using Arduino-compatible hardware, and it stores calibration data persistently using EEPROM.

## Features
- **Soil Moisture Sensor Calibration**: Supports both dry and wet soil calibration via physical buttons.
- **LCD Display**: Displays current soil moisture data and calibration information in real-time.
- **EEPROM**: Stores calibration data for persistence across power cycles.
- **Serial Commands**: Accepts commands over serial to set device name, change calibration values, and toggle debug modes.

## Hardware Requirements
- Arduino-compatible board
- Soil Moisture Sensor
- LCD with I2C Interface
- Push Buttons for Calibration

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software) or PlatformIO
- `EasyButton` library for handling button input
- `LiquidCrystal_I2C_Hangul` for display handling

## Installation
1. Clone the repository using SSH:
   ```sh
   git clone git@github.com:makers-multiverse/Monitor.git
   ```
2. Open the `Monitor.ino` sketch in the Arduino IDE or PlatformIO.
3. Compile and upload the sketch to your Arduino board.

## Usage
1. Power on the device, and the LCD will show "Soil Moisture" readings.
2. Press the first button to calibrate for dry soil.
3. Press the second button to calibrate for wet soil.
4. Use the serial interface to issue commands such as setting the device name or toggling debug mode.

## License
This project is licensed under the MIT License.