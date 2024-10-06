#include <Arduino.h>
#include "LoggerConfig.h"
#include "SerialLogger.h"
#include "SensorAnalog.h"
#include <EasyButton.h>
#include "SensorConfig.h"
#include "ButtonConfig.h"
#include "ActiveThreshold.h"
#include "ThresholdConfig.h"  // Include threshold configuration
#include "ControlConfig.h"    // Include control pin configuration

// Initialize sensor, buttons, and threshold
SensorAnalog SensorAnalog(SENSOR_PIN);  // Use SENSOR_PIN from SensorConfig.h
EasyButton button1(BUTTON1_PIN);        // Use BUTTON1_PIN from ButtonConfig.h
EasyButton button2(BUTTON2_PIN);        // Use BUTTON2_PIN from ButtonConfig.h
ActiveThreshold threshold;              // ActiveThreshold instance

void setup() {
    pinMode(CONTROL_PIN, OUTPUT);  // Use CONTROL_PIN for output (e.g., LED, pump)

    Logger.init(115200);  // Initialize Serial communication
    Logger.infoln("Starting...");

    // Sensor configuration
    SensorAnalog.setInterval(READING_INTERVAL);
    SensorAnalog.loadCalibration();
    SensorAnalog.onDataReceived(handleDataReceived);  // Pass sensor data to handleDataReceived

    // Button configuration for calibration
    button1.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.begin();
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize ActiveThreshold with values from ThresholdConfig
    threshold.init()
             .setDefaultThreshold(DEFAULT_THRESHOLD)  // Default threshold from config
             .loadThresholdFromEEPROM()               // Load stored threshold if available
             .setActiveHigh(IS_ACTIVE_HIGH)           // Active-high behavior from config
             .onActive(turnOnControl)                 // Control ON when active
             .onInactive(turnOffControl);             // Control OFF when inactive

    delay(1000);
}

int i = 1;

void loop() {
    button1.read();
    button2.read();

    SensorAnalog.loop();  // Process sensor data

    Logger.debug("Loop: ");
    Logger.debugln(i);
    i++;

    delay(1000);
}

// Calibration for low point
void onPressedCalibrateLow() {
    int raw = SensorAnalog.readRaw();
    
    Logger.info("Calibrating sensor low: ");
    Logger.infoln(raw);
    
    SensorAnalog.setCalibrationLow(raw);
    delay(1000);
}

// Calibration for high point
void onPressedCalibrateHigh() {
    int raw = SensorAnalog.readRaw();
    
    Logger.info("Calibrating sensor high: ");
    Logger.infoln(raw);
    
    SensorAnalog.setCalibrationHigh(raw);
    delay(1000);
}

// Handle sensor data and pass to ActiveThreshold for evaluation
void handleDataReceived(int value) {
    int rawValue = SensorAnalog.readRaw();

    Logger.data(SENSOR_LABEL, SENSOR_KEY, value);
    Logger.data("Raw", "R", rawValue);
    Logger.dataln();

    // Evaluate sensor value with the threshold
    threshold.evaluate(value);
}

// Callback to turn on the control (e.g., LED, pump)
void turnOnControl() {
    digitalWrite(CONTROL_PIN, HIGH);
    Logger.infoln("Control turned ON (Active)");
}

// Callback to turn off the control
void turnOffControl() {
    digitalWrite(CONTROL_PIN, LOW);
    Logger.infoln("Control turned OFF (Inactive)");
}