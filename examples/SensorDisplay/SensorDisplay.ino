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
    DisplayValueLCD display(0x27, 16, 2);  // LCD I2C address and dimensions
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
    #include "DisplayValueOLED.h"
    DisplayValueOLED display;  // OLED instance
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_NONE
    #include "DisplayValueNull.h"
    DisplayValueNull display;  // Null display instance
#endif

// Initialize sensor and buttons
SensorAnalog sensor(SENSOR_PIN);
EasyButton button1(BUTTON1_PIN);
EasyButton button2(BUTTON2_PIN);

void setup() {
    Logger.init(115200);
    Logger.infoln("Starting Sensor Display...");  // Initialize logger with message

    // Log the display type for confirmation
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
        Logger.debugln("Display type: LCD");
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
        Logger.debugln("Display type: OLED");
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_NONE
        Logger.debugln("Display type: None");
    #endif

    sensor.setCalibrationDefaultLow(DEFAULT_CALIBRATION_LOW)        // Default low from config
          .setCalibrationDefaultHigh(DEFAULT_CALIBRATION_HIGH)    // Default high from config
          .loadCalibration()                  // Load saved calibration, or use defaults
          .setInterval(READING_INTERVAL)      // Set reading interval
          .onDataReceived(handleDataReceived); // Register data handler

    button1.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);  // Button 1 for low calibration
    button2.begin();
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh); // Button 2 for high calibration

    display.init();
    display.setLabel(SENSOR_LABEL);  // Initialize display with sensor label
    display.setSuffix("%");         // Set unit suffix
    delay(1000);                    // Allow setup time
}

void loop() {
    button1.read();
    button2.read();
    sensor.loop();  // Handle sensor updates
    delay(10);      // Short delay for responsiveness
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

// Handle sensor data: log and display sensor readings
void handleDataReceived(int value) {
    int rawValue = sensor.readRaw();
    Logger.data(SENSOR_LABEL, SENSOR_KEY, value);  // Calibrated value passed in
    Logger.data("Raw", "R", rawValue);             // Optional: logs the raw value for reference
    Logger.dataln();
    display.setValue(value);
}
