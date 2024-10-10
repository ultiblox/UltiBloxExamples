#include <Arduino.h>
#include "LoggerConfig.h"
#include "SerialLogger.h"
#include "SensorAnalog.h"
#include <EasyButton.h>
#include "DisplayConfig.h"
#include "SensorConfig.h"
#include "ButtonConfig.h"

#if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
    #include "DisplayValueOLED.h"
    DisplayValueOLED display;
#endif

// Initialize sensor and buttons based on the configuration
SensorAnalog SensorAnalog(SENSOR_PIN);  // Use SENSOR_PIN from SensorConfig.h
EasyButton button1(BUTTON1_PIN);        // Use BUTTON1_PIN from ButtonConfig.h
EasyButton button2(BUTTON2_PIN);        // Use BUTTON2_PIN from ButtonConfig.h

void setup() {
    Logger.init(115200);  // Initialize Serial communication
    Logger.infoln("Starting...");

    // Sensor configuration
    SensorAnalog.setInterval(READING_INTERVAL);
    SensorAnalog.loadCalibration();
    SensorAnalog.onDataReceived(handleDataReceived);

    // Button configuration
    button1.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.begin();
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize the OLED display
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
        Logger.debugln("Display type: OLED");
        display.init();
    #endif

    display.setLabel(SENSOR_LABEL);

    delay(1000);

    display.setSuffix("%");
}

int i = 1;

void loop() {
    button1.read();
    button2.read();

    SensorAnalog.loop();

    Logger.debug("Loop: ");
    Logger.debugln(i);
    i++;

    delay(1000);
}

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

void handleDataReceived(int value) {
    int rawValue = SensorAnalog.readRaw();

    Logger.data(SENSOR_LABEL, SENSOR_KEY, value);
    Logger.data("Raw", "R", rawValue);
    Logger.dataln();

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
      display.setValue(value);
    #endif
}
