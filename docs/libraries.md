# UltiBlox Libraries Guide

This guide provides detailed information about each core library in the UltiBlox ecosystem. These libraries enable modular control of sensors, displays, logging, and threshold-based actions for Arduino projects. Each library is designed to be used independently or combined with others.

## Logging Libraries

### [SerialLogger](https://github.com/ultiblox/SerialLogger)
   - A versatile logging library that enables debugging and data logging over Serial. Suitable for monitoring real-time data and debugging project code.

## Sensor Handling Libraries

### [SensorAnalog](https://github.com/ultiblox/SensorAnalog)
   - Reads and calibrates data from analog sensors, with support for applying calibration ranges and setting threshold-based callbacks.

## Display Libraries

### [DisplayValueLCD](https://github.com/ultiblox/DisplayValueLCD)
   - Manages data display on I2C-connected LCD screens, making it easy to render values from sensors or other sources.

### [DisplayValueOLED](https://github.com/ultiblox/DisplayValueOLED)
   - Enables text and graphics rendering on OLED displays using U8x8lib, ideal for high-resolution display needs.

## Control & Threshold Libraries

### [ActiveThreshold](https://github.com/ultiblox/ActiveThreshold)
   - Automates control actions based on sensor data, activating or deactivating outputs when sensor values cross predefined thresholds.
