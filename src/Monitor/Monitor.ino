#include <SensorAnalog.h>
#include <EasyButton.h>
#include "DisplayConfig.h"

#if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
    #include "DisplayValueLCD.h"
    DisplayValueLCD display(0x27, 16, 2);
#elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
    #include "DisplayValueOLED.h"
    DisplayValueOLED display;
#endif

#define SENSOR_PIN A0
// #define SENSOR_LABEL "Soil Moisture"
#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define LONG_PRESS_DURATION 1000

const char* const SENSOR_LABEL = "Soil Moisture";

SensorAnalog SensorAnalog(SENSOR_PIN);
EasyButton button1(BUTTON1_PIN);
EasyButton button2(BUTTON2_PIN);

void setup() {
    Serial.begin(115200);

    SensorAnalog.setInterval(1000);
    SensorAnalog.loadCalibration();
    SensorAnalog.setCallback(handleSensorData);

    button1.begin();
    button2.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize the display based on the type of display being used
    #if ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_LCD
      display.init();
    #elif ACTIVE_DISPLAY_TYPE == DISPLAY_TYPE_OLED
      
          // display.setLabelFont(u8g2_font_ncenB08_tr); // Example smaller font for label
          // display.setValueFont(u8g2_font_ncenB14_tr);                    // Assuming 12 pixels average width for value font
          display.init();
    #endif

    delay(1000);
    display.setLabel("Starting...");  // Set initial message on the display
}


void loop() {
    button1.read();
    button2.read();
    SensorAnalog.loop();
    delay(1000);
}


void onPressedCalibrateLow() {
    Serial.println("Calibrated low");
    SensorAnalog.setCalibrationLow(SensorAnalog.readRaw());

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
    display.clear();
    display.setLabel("Calibrated low");
    delay(1000);
    #endif
}

void onPressedCalibrateHigh() {
    Serial.println("Calibrated high");
    SensorAnalog.setCalibrationHigh(SensorAnalog.readRaw());

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
    display.clear();
    display.setLabel("Calibrated high");
    delay(1000);
    #endif
}

void handleSensorData(int value) {
    int rawValue = SensorAnalog.readRaw();
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print(", Calibrated: ");
    Serial.print(value);
    Serial.print(", Low: ");
    Serial.print(SensorAnalog.readCalibrationLow());
    Serial.print(", High: ");
    Serial.print(SensorAnalog.readCalibrationHigh());
    Serial.println();

    #if ACTIVE_DISPLAY_TYPE != DISPLAY_TYPE_NONE
    display.setLabel(SENSOR_LABEL);
    display.updateValue(String(value) + "%");
    #endif
}
