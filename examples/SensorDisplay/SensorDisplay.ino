#include <Arduino.h>
#include "LoggerConfig.h"
#include "SerialLogger.h"
#include "SensorAnalog.h"
#include <EasyButton.h>
#include "DisplayConfig.h"
#include "SensorConfig.h"
#include "ButtonConfig.h"

// Conditionally include and instantiate the correct display based on configuration
#if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
    #include "DisplayValueLCD.h"
    DisplayValueLCD display(0x27, 16, 2);
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
    #include "DisplayValueOLED.h"
    DisplayValueOLED display;
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_NONE
    #include "DisplayValueNull.h"
    DisplayValueNull display;  // Null display instance
#endif

// Initialize sensor, buttons, and threshold
SensorAnalog sensor(SENSOR_PIN);  // Use SENSOR_PIN from SensorConfig.h
EasyButton button1(BUTTON1_PIN);        // Use BUTTON1_PIN from ButtonConfig.h
EasyButton button2(BUTTON2_PIN);        // Use BUTTON2_PIN from ButtonConfig.h

void setup() {
    Logger.init(115200);
    Logger.infoln("Starting Sensor Display...");  // Initialize logger with message

    Logger.init(115200);  // Initialize Serial communication
    Logger.infoln("Starting...");

    // Sensor configuration
    sensor.setInterval(READING_INTERVAL);
    sensor.setCalibrationDefaultHigh(DEFAULT_CALIBRATION_HIGH); // Set calibration defaults
    sensor.setCalibrationDefaultLow(DEFAULT_CALIBRATION_LOW);
    // NOTE: Directly setting calibration in code is not recommended. It will overwrite any changes made by the user.
    // This should generally only be used for testing/debugging, or to reset calibration. For production, only set calibration 'defaults' in code.
    // Set calibration in eeprom (to override defaults)
    // sensor.setCalibrationHigh(0);
    // sensor.setCalibrationLow(1024);
    sensor.loadCalibration();
    sensor.onDataReceived(handleDataReceived);

    // Button configuration for calibration
    button1.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.begin();
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize the display
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
        Logger.debugln("Display type: LCD");
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
        Logger.debugln("Display type: OLED");
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_NONE
        Logger.debugln("Display type: None");
    #endif

    display.init();
    display.setLabel(SENSOR_LABEL);  // Initialize display with sensor label
    display.setSuffix("%");         // Set unit suffix
    delay(1000);                    // Allow setup time
}

void loop() {
    button1.read();
    button2.read();

    sensor.loop();  // Process sensor data

    delay(10);
}

// Calibration function for setting the low point
void onPressedCalibrateLow() {
    int raw = sensor.readRaw();
    Logger.info("Calibrating low point: ");
    Logger.infoln(raw);
    sensor.setCalibrationLow(raw);

    display.setLabel("Low");
    display.setSuffix(" raw");
    display.setValue(raw);
    delay(1000);
    display.setLabel(SENSOR_LABEL);
    display.setSuffix("%");  // Restore main label and units
}

// Calibration function for setting the high point
void onPressedCalibrateHigh() {
    int raw = sensor.readRaw();
    Logger.info("Calibrating high point: ");
    Logger.infoln(raw);
    sensor.setCalibrationHigh(raw);

    display.setLabel("High");
    display.setSuffix(" raw");
    display.setValue(raw);
    delay(1000);
    display.setLabel(SENSOR_LABEL);
    display.setSuffix("%");  // Restore main label and units
}

void handleDataReceived(int value) {
    int rawValue = sensor.readRaw();
    Logger.data(SENSOR_LABEL, SENSOR_KEY, value);  // Calibrated value passed in
    Logger.data("Raw", "R", rawValue);             // Optional: logs the raw value for reference
    Logger.dataln();

    display.setValue(value);
}
