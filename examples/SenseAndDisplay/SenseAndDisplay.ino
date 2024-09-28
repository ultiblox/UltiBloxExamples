#include <Arduino.h>
#include "LoggerConfig.h"
#include "SerialLogger.h"
#include "SensorAnalog.h"
#include <EasyButton.h>
#include "DisplayConfig.h"
#include "SensorConfig.h"
#include "ButtonConfig.h"

#if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
    #include "DisplayValueLCD.h"
    DisplayValueLCD display(0x27, 16, 2);
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
    #include "DisplayValueOLED.h"
    DisplayValueOLED display;
#endif

// Initialize sensor and buttons based on the configuration
SensorAnalog SensorAnalog(SENSOR_PIN);  // Use SENSOR_PIN from SensorConfig.h
EasyButton button1(BUTTON1_PIN);        // Use BUTTON1_PIN from ButtonConfig.h
EasyButton button2(BUTTON2_PIN);        // Use BUTTON2_PIN from ButtonConfig.h

void setup() {
    Logger.init(115200);  // Initialize Serial communication
    Logger.logln("Starting...");

    // Sensor configuration
    SensorAnalog.setInterval(READING_INTERVAL);
    SensorAnalog.loadCalibration();
    SensorAnalog.onDataReceived(handleDataReceived);

    // Button configuration
    button1.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.begin();
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize the display
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
        Logger.logln("Display type: LCD");
        display.init();
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
        Logger.logln("Display type: OLED");
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

    delay(1000);
}

void onPressedCalibrateLow() {
    Logger.logln("Calibrating sensor low");

    int raw = SensorAnalog.readRaw();
    SensorAnalog.setCalibrationLow(raw);

    display.setLabel("Low");
    display.setSuffix(" raw");
    display.setValue(raw);

    delay(1000);

    display.setLabel(SENSOR_LABEL);
    display.setSuffix("%");
}

void onPressedCalibrateHigh() {
    Logger.logln("Calibrating sensor high");

    int raw = SensorAnalog.readRaw();
    SensorAnalog.setCalibrationHigh(raw);

    display.setLabel("High");
    display.setSuffix(" raw");
    display.setValue(raw);

    delay(1000);

    display.setLabel(SENSOR_LABEL);
    display.setSuffix("%");
}

void handleDataReceived(int value) {
    int rawValue = SensorAnalog.readRaw();

    Serial.print(SENSOR_LABEL);
    Serial.print(": ");
    Serial.print(value);
    Serial.print("%, ");
    Serial.println();

    display.setValue(value);
}
