# UltiBlox Examples Guide

This guide provides an overview of the example sketches available in UltiBloxExamples. Each example demonstrates different ways to work with UltiBlox libraries. For further details on specific libraries used, please refer to their respective GitHub repositories.

---

## Available Examples

### SensorControl
- **Purpose**: Demonstrates basic sensor control functionality with threshold activation using `ActiveThreshold`.
- **Description**: Reads sensor inputs and controls outputs based on defined thresholds, with calibration through button presses.
- **Related Libraries**: [SensorAnalog](https://github.com/ultiblox/SensorAnalog), [ActiveThreshold](https://github.com/ultiblox/ActiveThreshold)

### SensorDisplayLCD
- **Purpose**: Outputs sensor data to an LCD screen.
- **Description**: Displays sensor values on an LCD screen, useful for monitoring setups. Includes calibration buttons for setting sensor range.
- **Related Libraries**: [DisplayValueLCD](https://github.com/ultiblox/DisplayValueLCD), [SensorAnalog](https://github.com/ultiblox/SensorAnalog)

### SensorDisplayOLED
- **Purpose**: Outputs sensor data to an OLED display.
- **Description**: Similar to `SensorDisplayLCD` but outputs data on an OLED display for high-resolution readouts.
- **Related Libraries**: [DisplayValueOLED](https://github.com/ultiblox/DisplayValueOLED), [SensorAnalog](https://github.com/ultiblox/SensorAnalog)

### SensorControlDisplayLCD
- **Purpose**: Combines sensor control with LCD display.
- **Description**: Integrates control features from `SensorControl` and displays the data on an LCD screen. Allows threshold adjustments through button interactions.
- **Related Libraries**: [DisplayValueLCD](https://github.com/ultiblox/DisplayValueLCD), [SensorAnalog](https://github.com/ultiblox/SensorAnalog), [ActiveThreshold](https://github.com/ultiblox/ActiveThreshold)

---

## Configuration and Customization

Each example relies on configuration files like `SensorConfig.h`, `ThresholdConfig.h`, `DisplayConfig.h`, and `ControlConfig.h` to set parameters like sensor pins, threshold levels, and display settings. Refer to the library documentation for specific configuration options.

---

## Building the Examples

To compile all examples, run the `build.sh` script:

```bash
bash build.sh
```

For further configuration options, refer to each library's GitHub page and configuration files as noted in each example's README.
