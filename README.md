# UniversalMakerBox

**UniversalMakerBox** is an open-source platform designed to help makers easily create Arduino-based projects using modular libraries and example sketches. Whether you're a beginner looking to start your first project or an experienced user wanting to build custom solutions, **UniversalMakerBox** provides the tools to help you succeed.

- **Flexible Hardware**: Use your own sensors, displays, and microcontrollers or source components from a kit.
- **Open-Source Libraries**: Helper libraries that simplify reading sensors, logging data, and displaying information.
- **3D Printable Enclosures**: Make your projects look polished by printing your own cases.

---

## Libraries

**UniversalMakerBox** is powered by several key libraries, each designed to work together seamlessly. You can find more detailed information on each library via the links below:

- [SerialLogger](#): Logs data to the serial interface for easy debugging and analysis.
- [DisplayValueLCD](#): Displays sensor readings on an LCD screen.
- [DisplayValueOLED](#): Displays sensor readings on an OLED screen.
- [SensorAnalog](#): Reads and processes data from analog sensors.

---

## Installation

You have three options for installing and using the UniversalMakerBox:

### 1. Using the Arduino IDE

- Download or clone the project files and open the sketch you want to use.
- Follow the [Arduino IDE setup guide](#) to install libraries and upload the sketch to your board.
- Install any required libraries using the Arduino Library Manager.

### 2. Using Arduino CLI

- Clone the repository and open a terminal:
  
  ```bash
  git clone https://github.com/YourRepo/UniversalMakerBox.git
  cd UniversalMakerBox
  ```

- Compile and upload a sketch using Arduino CLI:
  
  ```bash
  arduino-cli compile --fqbn arduino:avr:uno your-sketch.ino
  arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:uno your-sketch.ino
  ```

### 3. Quick Start via Script

- For fast setup, use this script to download and install everything you need:
  
  ```bash
  curl -fsSL https://raw.githubusercontent.com/YourRepo/UniversalMakerBox/master/install.sh | bash
  ```

---

## Hardware and Enclosures

The hardware used with **UniversalMakerBox** depends on the project you're working on. Here are a few example setups:

- **Soil Moisture Monitor**: Arduino Uno, LCD display, soil moisture sensor.
- **Temperature Monitor**: Arduino Nano, OLED display, temperature sensor.

The 3D printable designs for enclosures can be found on [Thingiverse](#).

---

## Example: Sense and Display

The **SenseAndDisplay** sketch demonstrates how to use **UniversalMakerBox** to read data from an analog sensor, display the results on an LCD or OLED, and calibrate the sensor using two buttons.

**Features**:

- **Sensor Reading**: Continuously reads data from an analog sensor (e.g., light, soil moisture).
- **Flexible Display**: Supports both LCD and OLED displays.
- **Calibration**: Use two buttons to set the low and high calibration points for the sensor without modifying the code.
- **Logging**: Logs sensor readings to the serial monitor for real-time monitoring.

#### How to Run This Example:

1. **Hardware Setup**:
   
   - Connect an analog sensor (e.g., light sensor or soil moisture sensor) to pin `A0`.
   - Connect two buttons to pins `3` and `4` for calibration.
   - Connect either an LCD or OLED display as per your configuration.

2. **Configure the Example**:
   
   - Open `DisplayConfig.h` to select your display type:
     
     ```cpp
     #define ACTIVE_DISPLAY_TYPE DISPLAY_TYPE_LCD  // or DISPLAY_TYPE_OLED
     ```
   
   - Adjust pin configurations in `ButtonConfig.h` and `SensorConfig.h` if needed.

3. **Upload the Sketch**:
   
   - Use the **Arduino IDE** or **Arduino CLI** to upload the sketch to your board.

4. **Run the Project**:
   
   - Once the sketch is uploaded, the display will show sensor readings as a percentage.
   - Use button 1 to set the "low" calibration point (e.g., dry soil) and button 2 to set the "high" point (e.g., fully wet soil).

#### Customization:

- You can change the sensor label by editing `SensorConfig.h`:
  
  ```cpp
  const char* const SENSOR_LABEL = "Light";   // Change to "Moisture" for soil monitoring
  ```

- Modify the sensor reading interval by changing `READING_INTERVAL` in `SensorConfig.h`.

---

## Contributing

We welcome contributions! If you want to report an issue, request a feature, or submit a pull request, please check out our [contributing guidelines](#).

---

## License

This project is licensed under the MIT License.