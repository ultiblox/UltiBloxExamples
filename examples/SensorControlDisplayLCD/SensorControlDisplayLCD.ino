#include <Arduino.h>
#include "LoggerConfig.h"
#include "SerialLogger.h"
#include "SensorAnalog.h"
#include <EasyButton.h>
#include "DisplayConfig.h"
#include "SensorConfig.h"
#include "ButtonConfig.h"
#include "ActiveThreshold.h"
#include "ThresholdConfig.h"
#include "ControlConfig.h"

#if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
    #include "DisplayValueLCD.h"
    DisplayValueLCD display(0x27, 16, 2);
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
    #include "DisplayValueOLED.h"
    DisplayValueOLED display;
#endif

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
    SensorAnalog.setCalibrationDefaultHigh(0); // Set calibration defaults
    SensorAnalog.setCalibrationDefaultLow(1024);
    // NOTE: Directly setting calibration in code is not recommended. It will overwrite any changes made by the user.
    // This should generally only be used for testing/debugging, or to reset calibration. For production, only set calibration 'defaults' in code.'
    // Set calibration in eeprom (to override defaults)
    // SensorAnalog.setCalibrationHigh(0);
    // SensorAnalog.setCalibrationLow(1024);
    SensorAnalog.loadCalibration();
    SensorAnalog.onDataReceived(handleDataReceived);

    // Button configuration for calibration
    button1.begin();
    button1.onPressed(onPressThresholdDown);
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.begin();
    button2.onPressed(onPressThresholdUp);
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize ActiveThreshold with values from ThresholdConfig
    threshold.init()
             .setDefaultThreshold(DEFAULT_THRESHOLD)  // Default threshold from config
             .loadThresholdFromEEPROM()               // Load stored threshold if available
             .setActiveHigh(IS_ACTIVE_HIGH)           // Active-high behavior from config
             .onActive(turnOnControl)                 // Control ON when active
             .onInactive(turnOffControl);             // Control OFF when inactive

    // Initialize the display
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
        Logger.debugln("Display type: LCD");
        display.init();
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
        Logger.debugln("Display type: OLED");
        display.init();
    #endif

    display.setLabel(SENSOR_LABEL);

    delay(1000);

    display.setSuffix("%");
}

void loop() {
    button1.read();
    button2.read();

    SensorAnalog.loop();  // Process sensor data

    delay(10);
}

// Calibration for low point
void onPressedCalibrateLow() {
    int raw = SensorAnalog.readRaw();
    
    Logger.info("Calibrating sensor low: ");
    Logger.infoln(raw);
    
    SensorAnalog.setCalibrationLow(raw);

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setLabel("Low");
      display.setSuffix(" raw");
      display.setValue(raw);
    #endif

    delay(1000);

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setLabel(SENSOR_LABEL);
      display.setSuffix("%");
    #endif
}

void onPressedCalibrateHigh() {
    int raw = SensorAnalog.readRaw();
    
    Logger.info("Calibrating sensor high: ");
    Logger.infoln(raw);
    
    SensorAnalog.setCalibrationHigh(raw);

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setLabel("High");
      display.setSuffix(" raw");
      display.setValue(raw);
    #endif

    delay(1000);

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setLabel(SENSOR_LABEL);
      display.setSuffix("%");
    #endif
}

// Handle sensor data and pass to ActiveThreshold for evaluation
void handleDataReceived(int value) {
    int rawValue = SensorAnalog.readRaw();

    Logger.data(SENSOR_LABEL, SENSOR_KEY, value);
    Logger.data("Raw", "R", rawValue);
    Logger.dataln();

    // Evaluate sensor value with the threshold
    threshold.evaluate(value);

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setLabel(SENSOR_LABEL);
      display.setValue(value);
    #endif
}

// Callback to turn on the control (e.g., LED, pump)
void turnOnControl() {
    digitalWrite(CONTROL_PIN, HIGH);
    Logger.infoln("Control ON (Active)");
}

// Callback to turn off the control
void turnOffControl() {
    digitalWrite(CONTROL_PIN, LOW);
    Logger.infoln("Control OFF (Inactive)");
}

void onPressThresholdDown() {    
    threshold.decrementThreshold();
    
    showThreshold();  
}

void onPressThresholdUp() {
    threshold.incrementThreshold();
    
    showThreshold();  
}

void showThreshold() {
    int currentThreshold = threshold.getThreshold();
    
    Logger.info("Threshold up: ");
    Logger.infoln(currentThreshold);

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setLabel("Threshold");
      display.setValue(currentThreshold);
    #endif

    delay(800);
}