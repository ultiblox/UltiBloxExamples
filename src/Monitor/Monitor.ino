
#include <Arduino.h>
#include "LoggerConfig.h"
#include "SerialLogger.h"
#include <SensorAnalog.h>
#include <EasyButton.h>
#include "DisplayConfig.h"
#include "SensorConfig.h"
#include "ButtonConfig.h"

#if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
    #include "DisplayValueLCD.h"
    DisplayValueLCD display(0x27, 16, 2);
// #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
//     #include "DisplayValueOLED.h"
//     DisplayValueOLED display;
#endif

// Initialize sensor and buttons based on the configuration
SensorAnalog SensorAnalog(SENSOR_PIN);  // Use SENSOR_PIN from SensorConfig.h
EasyButton button1(BUTTON1_PIN);        // Use BUTTON1_PIN from ButtonConfig.h
EasyButton button2(BUTTON2_PIN);        // Use BUTTON2_PIN from ButtonConfig.h

void setup() {
    Serial.begin(115200);
    Serial.println("System starting...");
    LOG_INFO("Booting...");

    // Sensor configuration
    SensorAnalog.setInterval(READING_INTERVAL);
    SensorAnalog.loadCalibration();
    SensorAnalog.setCallback(handleSensorData);

    // Button configuration
    button1.begin();
    button2.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize the display
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
        LOG_INFO("Display type: LCD");
        display.init();
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
        LOG_INFO("Display type: OLED");
        display.init();
    #endif

    display.setLabel(SENSOR_LABEL);
    display.updateValue("Loading...");

    delay(1000);
}

void loop() {
    button1.read();
    button2.read();

    SensorAnalog.loop();

    delay(1000);
}

void onPressedCalibrateLow() {
    LOG_INFO("Calibrating sensor low");

    int raw = SensorAnalog.readRaw();
    SensorAnalog.setCalibrationLow(raw);

    display.setLabel("Low");
    display.updateValue(String(raw));

    delay(1000);
}

void onPressedCalibrateHigh() {
    LOG_INFO("Calibrating sensor high");

    int raw = SensorAnalog.readRaw();
    SensorAnalog.setCalibrationHigh(raw);

    display.setLabel("High");
    display.updateValue(String(raw));

    delay(1000);
}

void handleSensorData(int value) {
    int rawValue = SensorAnalog.readRaw();

    Serial.println(String(SENSOR_LABEL) + ": " + String(value) + "%");
    Serial.println("Raw sensor value: " + String(rawValue));

    display.setLabel(SENSOR_LABEL);
    display.updateValue(String(value) + "%");
}
