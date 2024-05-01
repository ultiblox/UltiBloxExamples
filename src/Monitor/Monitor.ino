#include <AnalogSensor.h>
#include <EasyButton.h>
#include "LCD1602Display.h" // Include your new display class

#define BUTTON1_PIN 3
#define BUTTON2_PIN 4
#define LONG_PRESS_DURATION 1000

AnalogSensor analogSensor(A0); // Create an instance of the AnalogSensor on pin A0
EasyButton button1(BUTTON1_PIN);
EasyButton button2(BUTTON2_PIN);

DisplayInterface* display; // Pointer to the abstract display class

void onPressedCalibrateLow() {
    Serial.println("Calibrated low");
    analogSensor.setCalibrationLow(analogSensor.readRaw());

    display->clear();
    display->setLabel("Calibrated low");
    delay(1000);
}

void onPressedCalibrateHigh() {
    Serial.println("Calibrated high");
    analogSensor.setCalibrationHigh(analogSensor.readRaw());

    display->clear();
    display->setLabel("Calibrated high");
    delay(1000);
}

void handleSensorData(int value) {
    int rawValue = analogSensor.readRaw();
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print(", Calibrated: ");
    Serial.print(value);
    Serial.print(", Low: ");
    Serial.print(analogSensor.readCalibrationLow());
    Serial.print(", High: ");
    Serial.print(analogSensor.readCalibrationHigh());
    Serial.println();

    display->updateValue(String(value) + "%");
}

void setup() {
    Serial.begin(115200);
    analogSensor.setInterval(1000);
    analogSensor.loadCalibration();
    analogSensor.setCallback(handleSensorData);

    button1.begin();
    button2.begin();
    button1.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateLow);
    button2.onPressedFor(LONG_PRESS_DURATION, onPressedCalibrateHigh);

    // Initialize the specific display
    display = new LCD1602Display(0x27, 16, 2);
    display->init();
    display->setLabel("Starting...");

    delay(1000);

    display->clear();
    display->setLabel("Soil Moisture");
}

void loop() {
    button1.read();
    button2.read();
    analogSensor.loop();
    delay(1000);
}
