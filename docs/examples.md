# UltiBlox Examples Guide

This guide provides an overview of the example sketches available in UltiBloxExamples. Each example demonstrates different ways to work with UltiBlox libraries. For further details on specific libraries used, please refer to their respective GitHub repositories.

---

## Available Examples

### SensorDisplay
- **Purpose**: Outputs sensor data to an LCD or OLED screen.
- **Description**: Displays sensor values on an LCD/OLED screen, useful for monitoring setups. Includes calibration buttons for setting sensor range.
- **Related Libraries**:  [SensorAnalog](https://github.com/ultiblox/SensorAnalog), [DisplayValueLCD](https://github.com/ultiblox/DisplayValueLCD), [DisplayValueOLED](https://github.com/ultiblox/DisplayValueOLED), [DisplayValueNull](https://github.com/ultiblox/DisplayValueNull)

### SensorControlDisplay
- **Purpose**: Combines sensor control with LCD or OLED display.
- **Description**: Integrates control features from `SensorControl` and displays the data on an LCD/OLED screen. Allows threshold adjustments through button interactions.
- **Related Libraries**: [SensorAnalog](https://github.com/ultiblox/SensorAnalog), [DisplayValueLCD](https://github.com/ultiblox/DisplayValueLCD), [DisplayValueOLED](https://github.com/ultiblox/DisplayValueOLED), [DisplayValueNull](https://github.com/ultiblox/DisplayValueNull) [ActiveThreshold](https://github.com/ultiblox/ActiveThreshold)

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
