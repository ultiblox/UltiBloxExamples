# Sense and Display Example

The **SenseAndDisplay** sketch demonstrates how to read data from an analog sensor (e.g., light or soil moisture sensor), display the results on an LCD or OLED screen, and calibrate the sensor using two buttons.

## Features

- **Sensor Reading**: Continuously reads data from an analog sensor.
- **Flexible Display**: Supports both LCD and OLED displays.
- **Calibration**: Use two buttons to set the low and high calibration points for the sensor.
- **Logging**: Logs sensor readings to the serial monitor for real-time monitoring.

---

## Hardware Setup

1. **Analog Sensor**:
   
   - Connect an analog sensor to pin `A0` (default in `SensorConfig.h`).

2. **Buttons**:
   
   - Connect button 1 to pin `3` (used for low calibration).
   - Connect button 2 to pin `4` (used for high calibration).

3. **Display**:
   
   - **LCD**: If using an LCD, connect it according to your display's I2C pin configuration.
   - **OLED**: If using an OLED, connect it to the appropriate I2C pins.

---

## Configure the Example

The example relies on multiple configuration files that allow you to customize the behavior of the sensor, display, buttons, and logging. Here's a breakdown of each file:

### **Configuring the Display** (DisplayConfig.h)

This file lets you select the type of display you're using:

```cpp
#define ACTIVE_DISPLAY_TYPE DISPLAY_TYPE_LCD  // or DISPLAY_TYPE_OLED
```

- **DISPLAY_TYPE_LCD**: Use this if you're using an I2C LCD display.
- **DISPLAY_TYPE_OLED**: Use this for OLED displays.

Make sure you select the correct display type to ensure the sketch interacts with the hardware properly.

### **Configuring Button Pins** (ButtonConfig.h)

This file defines the pins for the buttons used for sensor calibration and the long press duration:

```cpp
#define BUTTON1_PIN 3  // Pin for the low calibration button
#define BUTTON2_PIN 4  // Pin for the high calibration button
#define LONG_PRESS_DURATION 1000  // Duration (in milliseconds) for a long press
```

- **BUTTON1_PIN**: Used to set the "low" calibration point.
- **BUTTON2_PIN**: Used to set the "high" calibration point.
- **LONG_PRESS_DURATION**: Defines how long a button must be pressed to trigger calibration (in milliseconds).

### **Configuring Sensor Settings** (SensorConfig.h)

This file allows you to configure the sensor's pin, label, and reading interval.

- **SENSOR_PIN**: Defines the pin to which the analog sensor is connected (e.g., A0 for a light or soil moisture sensor).
  
  ```cpp
  #define SENSOR_PIN A0  // Pin connected to the analog sensor
  ```

- **SENSOR_LABEL**: Customize this label to match the type of sensor you're using (e.g., `"Moisture"` for a soil moisture sensor).
  
  ```cpp
  const char* const SENSOR_LABEL = "Moisture";  // For soil moisture monitoring
  ```

- **READING_INTERVAL**: Set the time (in milliseconds) between sensor readings. For example, changing it to `500` will take readings every half second.
  
  ```cpp
  #define READING_INTERVAL 500  // Read sensor data every 500 milliseconds
  ```
  
  ```
  
  ```

### **Configuring Logging** (LoggerConfig.h)

This file controls whether logging is enabled:

```cpp
#define SERIAL_LOGGER_ENABLED 1  // Set to 0 to disable serial logging
```

- Set to `1` to enable logging of sensor data and events to the serial monitor.
- Set to `0` to disable logging (useful if you want to reduce serial output).

---

## Upload the Sketch

### Arduino IDE

1. Open the **Arduino IDE** and select the correct board.
2. Upload the sketch to your board.

### Arduino CLI

For **Arduino CLI**, you can compile and upload the sketch using this command:

```bash
cd ~/workspace/UniversalMakerBox
export BOARD="nano"  # Change this to your board type (e.g., "uno", "nano", etc.)
export PORT="/dev/ttyUSB0"  # Change this to your specific port

# Compile and upload using the configured BOARD and PORT
arduino-cli compile --fqbn arduino:avr:$BOARD Devices/UniversalMakerBox/examples/SenseAndDisplay/SenseAndDisplay.ino && \
arduino-cli upload -p $PORT --fqbn arduino:avr:$BOARD Devices/UniversalMakerBox/examples/SenseAndDisplay/SenseAndDisplay.ino
```

Replace:

- '/dev/ttyUSB0' with the correct port for your device.

- 'nano' with the correct Arduino board.

---

## Calibration

Analog sensors typically return raw values in the range of 0 to 1024 (based on the Arduino’s ADC). These values need to be calibrated to convert them into more meaningful units, such as percentages. Calibration allows you to map this 0-1024 range to a percentage (0-100%) based on your specific setup.

### How Calibration Works

The calibration process involves setting reference points for the sensor:

- **Low Calibration**: Press and hold button 1 (connected to `BUTTON1_PIN`) to set the "low" calibration point. For example, if you're using a moisture sensor, this represents the dry soil condition (0%).
- **High Calibration**: Press and hold button 2 (connected to `BUTTON2_PIN`) to set the "high" calibration point. For a moisture sensor, this would represent fully wet soil (100%).

### Why Calibration Is Important

- The sensor’s raw 0-1024 output is converted to a percentage (0-100%) after calibration, making the sensor data more intuitive and relevant.
- Calibration ensures that your sensor readings are specific to your environment, which leads to more accurate measurements.

---

## How Data is Handled

The sketch uses the `onDataReceived` function, which is called whenever new sensor data is available. This function is responsible for processing and displaying the sensor readings. You can customize this function to handle the data in a different way if desired.

```cpp
void onDataReceived(int value) {
    int rawValue = SensorAnalog.readRaw();
    Serial.print(SENSOR_LABEL);
    Serial.print(": ");
    Serial.print(value);
    Serial.println("%");

    // Update the display with the new value
    display.setValue(value);
}
```

This function reads raw data from the sensor, logs it to the serial monitor, and updates the display with the latest sensor value.

---
