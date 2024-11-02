# Examples Overview

UltiBlox provides a set of modular examples that demonstrate how to use different hardware configurations, sensor readings, displays, and control mechanisms. Each example is designed to showcase specific features, making it easier for both beginners and experienced users to get started.

### 1. **SensorControl**
   - **Purpose**: Demonstrates how to read data from an analog sensor and control devices (like a pump or LED) based on sensor thresholds.
   - **Key Features**:
     - Read data from an analog sensor (e.g., soil moisture sensor).
     - Configure thresholds to trigger control actions (e.g., turn on/off a pump).
     - Logs sensor readings to the serial monitor.
   - **Hardware**:
     - Analog sensor (e.g., soil moisture sensor) connected to `A0`.
     - Device control (e.g., pump, LED) connected to a digital pin.
   - **Use Case**: Ideal for projects where you want to trigger actions based on sensor readings (e.g., automated watering system).

### 2. **SensorDisplay**
   - **Purpose**: Shows how to display sensor data on an LCD or OLED screen. It also includes calibration functionality to adjust sensor readings using two buttons.
   - **Key Features**:
     - Read sensor data and display it on an LCD or OLED screen.
     - Calibrate the sensor using buttons to set low and high values.
     - Logs sensor readings to the serial monitor for real-time feedback.
   - **Hardware**:
     - Analog sensor connected to `A0`.
     - LCD or OLED display.
     - Two buttons for sensor calibration (connected to pins `3` and `4`).
   - **Use Case**: Useful for projects where you need to visually monitor sensor readings (e.g., displaying soil moisture levels).

### 3. **SensorControlDisplay**
   - **Purpose**: Combines both sensor control and display functionality. This example reads data from a sensor, displays the values on a screen, and controls a device based on sensor thresholds.
   - **Key Features**:
     - Combines the features of **SensorControl** and **SensorDisplay**.
     - Read sensor data, display it, and control a device based on thresholds.
     - Calibrate the sensor using buttons.
     - Logs sensor data and actions to the serial monitor.
   - **Hardware**:
     - Analog sensor connected to `A0`.
     - LCD or OLED display.
     - Two buttons for calibration.
     - Device control pin for managing external devices (e.g., a pump or LED).
   - **Use Case**: Perfect for creating full-featured sensor monitoring systems that both display data and trigger actions.

---

### How to Use the Examples

Each example includes configuration files that allow you to customize the setup based on your hardware. Whether you are working with sensors, displays, or both, you can adapt these examples to fit your project needs.

For details on how to configure the sensors, displays, buttons, and thresholds, check the respective configuration files included with each example:
- **SensorConfig.h**: Configure sensor pins and intervals.
- **DisplayConfig.h**: Select the type of display (LCD or OLED).
- **ThresholdConfig.h**: Set sensor thresholds for control actions.
