# Sensor Display Example

The **SensorDisplay** example demonstrates how to read data from an analog sensor (e.g., a light or soil moisture sensor), display the results on an LCD or OLED screen, and calibrate the sensor using two buttons. It also supports a “null display” option to allow the code to run without displaying any data.

## Features

- **Sensor Reading**: Continuously reads data from an analog sensor.
- **Flexible Display**: Supports LCD, OLED, or a null display option.
- **Calibration**: Allows setting low and high calibration points to adjust sensor output to a meaningful range.
- **Logging**: Logs sensor readings to the serial monitor for real-time monitoring.

---

## Hardware Setup

1. **Analog Sensor**:
   - Connect an analog sensor to pin `A0` (or another pin if configured in `SensorConfig.h`).

2. **Buttons**:
   - Connect button 1 to pin `3` (for low calibration).
   - Connect button 2 to pin `4` (for high calibration).

3. **Display**:
   - **LCD**: For LCD displays, connect to I2C pins (e.g., `SDA` and `SCL`).
   - **OLED**: For OLED displays, connect to the appropriate I2C pins.
   - **No Display**: Select `DISPLAY_TYPE_NONE` to disable display output.

---

## Configuring the Example

This example uses configuration files for customizing the display, sensor, buttons, and logging settings. Here’s a breakdown of each configuration file:

### **1. Configuring the Display** (`DisplayConfig.h`)

Select the display type by uncommenting the line corresponding to the desired display:

```cpp
// Select the active display type by uncommenting one of the following lines:
#define ACTIVE_DISPLAY_TYPE DISPLAY_TYPE_LCD
//#define ACTIVE_DISPLAY_TYPE DISPLAY_TYPE_OLED
//#define ACTIVE_DISPLAY_TYPE DISPLAY_TYPE_NONE
```

- **DISPLAY_TYPE_LCD**: For an I2C LCD display.
- **DISPLAY_TYPE_OLED**: For an OLED display.
- **DISPLAY_TYPE_NONE**: Disables display output, using a “null display” instead.

### **2. Configuring Button Pins** (`ButtonConfig.h`)

Defines the pins for calibration buttons and the long press duration:

```cpp
#define BUTTON1_PIN 3  // Pin for low calibration button
#define BUTTON2_PIN 4  // Pin for high calibration button
#define LONG_PRESS_DURATION 1000  // Duration (in milliseconds) for a long press
```

- **BUTTON1_PIN**: Sets the "low" calibration point.
- **BUTTON2_PIN**: Sets the "high" calibration point.
- **LONG_PRESS_DURATION**: Time (in milliseconds) required for a long press to activate calibration.

### **3. Configuring Sensor Settings** (`SensorConfig.h`)

Defines sensor parameters such as the pin, label, reading interval, and a short key for machine-readable data:

- **SENSOR_PIN**: Connects to the analog sensor pin (e.g., `A0`).
  
  ```cpp
  #define SENSOR_PIN A0
  ```

- **SENSOR_LABEL**: Label for the sensor data (e.g., "Moisture").
  
  ```cpp
  const char* const SENSOR_LABEL = "Moisture";
  ```

- **SENSOR_KEY**: A short identifier for the sensor data, used for machine-readable output (e.g., "M" for moisture). This is helpful when logging data in a format that external systems or machines can interpret.

  ```cpp
  const char* const SENSOR_KEY = "M";
  ```

- **READING_INTERVAL**: Time interval (in milliseconds) between sensor readings.
  
  ```cpp
  #define READING_INTERVAL 500
  ```

- **Default Calibration Values**:
  - `DEFAULT_CALIBRATION_LOW` and `DEFAULT_CALIBRATION_HIGH` provide fallback values for the low and high calibration points before manual calibration.

  ```cpp
  #define DEFAULT_CALIBRATION_LOW 0
  #define DEFAULT_CALIBRATION_HIGH 1024
  ```

### **4. Configuring Logging** (`LoggerConfig.h`)

Enable or disable logging:

```cpp
#define SERIAL_LOGGER_ENABLED 1  // Set to 0 to disable serial logging
```

- Set to `1` to enable logging.
- Set to `0` to disable logging if not needed.

---

## Calibration

### Overview

Calibration maps the sensor’s raw output (0–1024) to a more meaningful range, such as 0–100%, making the sensor data useful and accurate. By default, the low and high calibration values are set in `SensorConfig.h` but can be refined through manual calibration.

### Calibration Process

- **Low Calibration**: Press and hold button 1 to set the "low" calibration point (e.g., dry soil).
- **High Calibration**: Press and hold button 2 to set the "high" calibration point (e.g., fully wet soil).

### EEPROM Persistence

Calibration values are stored in EEPROM, allowing them to persist across resets. If no calibration values are stored in EEPROM, the default values specified in `SensorConfig.h` will be used until manual calibration is performed.

---

## How Data is Handled

The sketch uses `handleDataReceived` to process incoming sensor data:

```cpp
void handleDataReceived(int value) {
    int rawValue = sensor.readRaw();
    Logger.data(SENSOR_LABEL, SENSOR_KEY, value);  // Calibrated value passed in
    Logger.data("Raw", "R", rawValue);             // Optional: logs the raw value for reference
    Logger.dataln();
    display.setValue(value);
}
```

- **Calibrated Value**: The `value` parameter represents the sensor output after calibration.
- **Raw Value**: Inside `handleDataReceived`, `sensor.readRaw()` retrieves the raw sensor reading, useful for debugging or comparison.

---

This README provides a comprehensive guide for configuring and running the `SensorDisplay` example, ensuring users have clear instructions for each feature and configuration option. Let me know if you have any additional requirements!
